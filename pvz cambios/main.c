#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"
#include "logica.h"
#include "guardado.h"
// Para compilar usar gcc -Wall -Wextra -o pvz main.c logica.c utils_map.c utils_config.c guardado.c, y luego ./pvz
// Pregunta el nivel de dificultad y retorna el archivo de configuracion que le corresponde
// Si no se escribe nada o el numero no es valido, se usa el nivel normal (por defecto)
const char* elegir_nivel() {
    char linea[20];
    int nivel = 2;
    printf("Elige el nivel:\n");
    printf("1. Facil\n");
    printf("2. Normal (por defecto)\n");
    printf("3. Dificil\n");
    printf("Nivel: ");
    if (fgets(linea, sizeof(linea), stdin) != NULL) {
        sscanf(linea, "%d", &nivel);
    }
    if (nivel == 1) {
        return "config_facil.txt";
    } else if (nivel == 3) {
        return "config_dificil.txt";
    }
    return "config_normal.txt";
}

void show_hud() {
    printf("\nAcciones:\n");
    printf("0. Cerrar juego\n");
    printf("1. Plantar Girasol\n");
    printf("2. Plantar Lanzaguisantes\n");
    printf("3. Plantar Nuez\n");
    printf("4. Pasar turno\n");
    printf("5. Plantar Jalapeno\n");
    printf("6. Plantar Patata Boom\n");
    printf("7. Guardar partida\n");
    printf("8. Cargar partida\n");
}

int main() {
    //semilla en caso de crear matriz aleatoria
    srand((unsigned int)time(NULL));

    //se elige el nivel y se lee su config
    Config config = {0};
    if (!load_config(elegir_nivel(), &config)) {
        printf("No se pudo cargar el archivo\n");
        return 1;
    }
    printf("Configuración cargada correctamente.\n");

    //carga mapa
    Jardin *mapa = load_map("mapa_ceros.txt", &config);
    if (!mapa) {
        printf("No se pudo cargar el mapa inicial\n");
        return 1;
    }
    printf("Mapa cargado con éxito (%d x %d).\n", mapa->fila, mapa->columna);

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

        //opcion para guardar la partida, no pasa el turno
        if (opcion == 7) {
            if (guardar_partida("partida.txt", mapa, soles, salud_casa, turno, oleada_actual, zombies_generados_oleada)) {
                printf("Partida guardada\n");
            } else {
                printf("No se pudo guardar la partida\n");
            }
            continue;
        }

        //opcion para cargar la partida, si falla se sigue con la partida actual
        if (opcion == 8) {
            Jardin *mapa_cargado = cargar_partida("partida.txt", &config, &soles, &salud_casa, &turno, &oleada_actual, &zombies_generados_oleada);
            if (mapa_cargado != NULL) {
                clear_map(mapa);
                mapa = mapa_cargado;
                printf("Partida cargada\n");
            } else {
                printf("No se pudo cargar la partida\n");
            }
            continue;
        }

        if ((opcion >= 1 && opcion <= 3) || opcion == 5 || opcion == 6) {//si input es plantar alguna planta, se determina la casilla donde se planta
            int f, c;
            printf("Ingresa fila (0 a %d) y columna (0 a %d): ", mapa->fila - 1, mapa->columna - 1);
            if (scanf("%d %d", &f, &c) == 2) {
                Tipo_casilla tipo = VACIO;
                if (opcion == 1){tipo = GIRASOL;
                }
                else if (opcion == 2){tipo = LANZAGUISANTE;
                }
                else if (opcion == 3){tipo = NUEZ;
                }
                else if (opcion == 5){tipo = JALAPENO;
                }
                else if (opcion == 6){tipo = PATATA_BOOM;
                }//si se planta en el rango adecuado
                if (plantar(mapa, f, c, tipo, &soles, &config)) {
                    printf("Plantado correctamente\n");
                }
                } else {//si no se planta en rango adecuado
                printf("Coordenadas invalidas, se omite turno\n");
                while (getchar() != '\n');
                }
        }

        avanzar_turno(mapa, &salud_casa, &soles, &config, &turno, &oleada_actual, &zombies_generados_oleada);

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

    //se libera memoria del mapa
    clear_map(mapa);

    return 0;
}
