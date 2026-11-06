#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils_config.h"
#include "utils_map.h"
#include "logica.h"

void show_hud() {
    printf("\nAcciones:\n");
    printf("0. Cerrar juego\n");
    printf("1. Plantar Girasol\n");
    printf("2. Plantar Lanzaguisantes\n");
    printf("3. Plantar Nuez\n");
    printf("4. Pasar turno\n");
}

int main() {
    //semilla en caso de crear matriz aleatoria
    srand((unsigned int)time(NULL));

    //se lee config
    Config config = {0};
    if (!load_config("config.txt", &config)) {
        printf("No se pudo cargar el archivo\n");
        return 1;
    }
    printf("Configuración cargada correctamente.\n");

    //carga mapa
    Jardin *mapa = load_map("mapa_ceros.txt");
    if (!mapa) {
        printf("No se pudo cargar el mapa inicial\n");
        return 1;
    }
    printf("Mapa cargado con éxito (%d x %d).\n", mapa->fila, mapa->columna);

    //matriz de vida
    int **matriz_vida = crear_matriz(mapa->fila, mapa->columna);
    if (!matriz_vida) {
        printf("No se pudo crear la matriz de vida\n");
        clear_map(mapa);
        return 1;
    }

    //inicializar variables
    int soles = config.sol_inicial;
    int salud_casa = config.vida_casa;
    int turno = 0;
    int oleada_actual = 1;
    int zombies_generados_oleada = 0;
    int estado_juego = 0;

    //ciclo de juego
    while (estado_juego == 0) {
        //muestra stats
        printf("\n==========================================");
        printf("\nTURNO: %d  |  OLEADA: %d/%d  |  SOLES: %d  |  SALUD CASA: %d\n", turno + 1, oleada_actual, config.max_oleadas, soles, salud_casa);
        printf("==========================================\n");
        print_map(mapa);

        //menu y input
        int opcion = 0;
        show_hud();
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 4;
        }
        //opcion para cerrar juego
        if (opcion == 0) {
            estado_juego = 2;
            break;
        }

        if (opcion >= 1 && opcion <= 3) {//si input es plantar alguna planta, se determina la casilla donde se planta
            int f, c;
            printf("Ingresa fila (0 a %d) y columna (0 a %d): ", mapa->fila - 1, mapa->columna - 1);
            if (scanf("%d %d", &f, &c) == 2) {
                Tipo_casilla tipo = VACIO;
                if (opcion == 1){tipo = GIRASOL;
                }
                else if (opcion == 2){tipo = LANZAGUISANTE;
                }
                else if (opcion == 3){tipo = NUEZ;
                }//si se planta en el rango adecuado
                if (plantar(mapa, matriz_vida, f, c, tipo, &soles, &config)) {
                    printf("Plantado correctamente\n");
                }
                } else {//si no se planta en rango adecuado
                printf("Coordenadas invalidas, se omite turno\n");
                while (getchar() != '\n');
                }
        }

        avanzar_turno(mapa, matriz_vida, &salud_casa, &soles, &config, &turno, &oleada_actual, &zombies_generados_oleada);

        //revisa si termina el loop
        estado_juego = revisar_fin_juego(mapa, salud_casa, &config, oleada_actual);
    }

    //mensaje post_partida
    print_map(mapa);
    if (estado_juego == 1) {
        printf("\nVictoria\n");
    } else if (estado_juego == -1) {
        printf("\nDerrota\n");
    } else if (estado_juego ==2){
        printf("\nJuego cerrado exitosamente\n");
    }

    //se libera memoria de matriz
    liberar_matriz(matriz_vida, mapa->fila);
    clear_map(mapa);

    return 0;
}