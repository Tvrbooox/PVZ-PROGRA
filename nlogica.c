#include "logica.h"
#include <stdlib.h>
#include <stdio.h>

// Funcion para limpiar las filas creadas en caso de fallo y evitar fugas
void liberar_matriz(int** m, int filas) {
    if (m == NULL){ // En caso de que no haya direccion de memoria 
        return;
    } // iteramos por cada fila hasta la que no se pudo crear y vamos eliminando las que quedaron "libres" para evitar uso de memoria innecesario
    for (int i = 0; i < filas; i++) {
        free(m[i]); // Eliminamos todas las filas creadas
    }
    free(m); // Finalmente eliminamos la matriz total
}

// Funcion Para la matriz como tablero de juego
int** crear_matriz(int filas, int columnas) {
    // Tratamos el caso de estar fuera de limites
    if (filas <= 0 || columnas <= 0){
      return NULL;   
    } 

    // Definimos la matriz usando malloc 
    int** m = malloc(filas * sizeof(int*));
    // Separamos el caso en el cual no se pudo reservar memoria
    if (m == NULL){
        return NULL;
    }

    // Recorremos las filas del tablero 
    for (int i = 0; i < filas; i++) {
        // En cada fila, ocupamos calloc para devolver una direccion de memoria de las columnas de la fila inicializadas en 0 (Calloc lo hace por defecto)
        m[i] = calloc(columnas, sizeof(int));
        // Si la direccion de memoria es nula
        if (m[i] == NULL) {
            // En caso que en una fila no haya direccion a una columna, entonces todo lo anterior debemos eliminarlo
            liberar_matriz(m, i);
            return NULL; // Salimos de la funcion ya que la matriz no se pudo crear
        }
    }
    return m; // Retorna el tablero de juego solo con ceros (celdas vacias/pastos)
}

// Imprimimos la matriz del juego
void imprimir_matriz(int** m, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }
}

// Funcion para plantar en el mapa
// Mapa es el tablero(Jardin), Matriz_Vida es la matriz con la vida de cada planta, f y c (Filas y columnas donde plantaremos),  
int plantar(Jardin *mapa, int **matriz_vida, int f, int c, Tipo_casilla tipo_planta, int *soles, Config *config) {

     // Condicional para no saltarnos los limites del juego
    if (f < 0 || f >= mapa->fila || c < 0 || c >= mapa->columna) {
        printf("Error: Posicion invalida.\n");
        return 0;
    }
    // Condicional en caso de que la casilla donde queramos plantar este ocupada
    if (mapa->grilla[f][c] != VACIO) {
        printf("Error: La casilla ya esta ocupada.\n");
        return 0; 
    }
    // Costo y vida de la planta elegida
    int costo = 0;
    int vida_inicial = 0;

    // Definimos cada personaje del juego entorno a los valores del struct
    if (tipo_planta == GIRASOL) {
        costo = config->cost_girasol; // Esto se lee como anda a donde apunta config y toma el valor de costo de girasol, y asi con cada personaje
        vida_inicial = config->vida_girasol;
    } else if (tipo_planta == LANZAGUISANTE) {
        costo = config->cost_lanzaguisante;
        vida_inicial = config->vida_lanzaguisante;
    } else if (tipo_planta == NUEZ) {
        costo = config->cost_nuez;
        vida_inicial = config->vida_nuez;
    }else{
        printf("Error: Tipo de planta invalido.\n");
        return 0;
    }

    // Verificamos si los soles que tenemos nos permite comprar la planta, si es asi, quitamos del total
    if (*soles >= costo) {
        *soles -= costo;
        // En el el struct mapa vamos a la grilla en la posicion f y c, y ponemos la planta seleccionada
        mapa->grilla[f][c] = tipo_planta;
        matriz_vida[f][c] = vida_inicial; // Guardamos en la matriz vida, la vida de ese tipo de planta
        return 1;  // Retornamos 1 si se planto
    } else {
        printf("Error: No tienes suficientes soles.\n");
        return 0;  // Retornamos 0 si no se planto
    }
}

// Funcion para ir gestionando la cantidad de soles que tiene el jugador
void gestion_soles(Jardin *mapa, int *soles_jugador, Config *config, int turno) {
    // Verifica si el turno actual coincide con la frecuencia de generacion de soles del cielo (ocupamos el resto)
    if (turno % config->frec_sol_base == 0) {
        *soles_jugador += config->valor_sol; 
        printf("Cayeron %d soles del cielo\n", config->valor_sol);
    }
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Si la casilla que estamos viendo era un girasol
            if (mapa->grilla[i][j] == GIRASOL) {
                // Revisa independientemente si coincide con el ciclo de producción de los girasoles.
                if (turno % config->frec_sol_girasol == 0) {
                    //entonces le sumamos la cantidad de soles que nos brinda el girasol
                    *soles_jugador += config->valor_sol;
                    printf("El girasol de la fila %d columna %d produjo %d soles\n", i, j, config->valor_sol);
                } 
            }
        }
    }
}

// Funcion para gestionar el ataque de las plantas
void ataques_plantas(Jardin *mapa, int **matriz_vida, Config *config, int turno) {
   // Si el turno actual no es múltiplo de la frecuencia de disparo, sale de la función inmediatamente 
    //  Los lanzaguisantes recargan en los turnos restantes, la idea del resto nos ayuda a forzar los turnos en los multiplos de la frecuencia
    if (turno % config->frec_lanzaguisante!= 0) {
        return; 
    }
    // Recorre cada posicion del tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Si la posicion era un lanzaguisantes
            if (mapa->grilla[i][j] == LANZAGUISANTE) {
                // Vemos una columna mas adelante (Derecha) para ver que tipo de entidad hay
                for (int k = j + 1; k < mapa->columna; k++) {
                    // Si encuentra al zombie base o al zombie bandera
                    if (mapa->grilla[i][k] == ZOMBIE_BASE || mapa->grilla[i][k] == ZOMBIE_FLAG) {
                        // Le quita el daño estipulado por el lanzaguisantes al zombie mediante lo establecido en la configuracion
                        matriz_vida[i][k] -= config->dmg_lanzaguisante; // Actualizamos la matriz de vida del zombie restandole el daño causado por el lanzaguisantes
                        break; 
                    }
                }
            }
        }
    }
}

// Funcion para gestionas el ataque de los zombies
void ataques_zombies(Jardin *mapa, int **matriz_vida, Config *config, int turno) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 1; j < mapa->columna; j++) { 
            // Variable bandera para controlar los ataques del zombie
            int le_toca_atacar = 0;

            // Verificamos el tipo de zombie y si su turno actual coincide con su velocidad de ataque
            if (mapa->grilla[i][j] == ZOMBIE_BASE && (turno % config->vel_zombie_base == 0)) {
                //Actualizamos la bandera, para que el zombie pueda atacar a la planta adyacente
                le_toca_atacar = 1;
            } 
            else if (mapa->grilla[i][j] == ZOMBIE_FLAG && (turno % config->vel_zombie_flag == 0)) {
                le_toca_atacar = 1;
            }

            // Si el zombie puede atacar, verificamos cual es la planta en la posicion adyacente
            if (le_toca_atacar == 1) {
                if (mapa->grilla[i][j-1] == GIRASOL || mapa->grilla[i][j-1] == LANZAGUISANTE || mapa->grilla[i][j-1] == NUEZ) {
                    // El zombie ataca quitando el daño estipulado a la planta correspondiente
                    matriz_vida[i][j-1] -= config->dmg_zombie_base; // Actualizamos la vida de la planta a su izquierda restandole el daño que le causo el zombie, el cual es lo mismo para los dos
                }
            }
        }
    }
}

// Funcion para limpiar entidades, que han muerto
void limpiar_muertos(Jardin *mapa, int **matriz_vida) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Si la posicion del tablero no es vacia, es decir hay una entidad
            if (mapa->grilla[i][j] != VACIO) {
                // y ademas la vida de esa entidad es menor o igual que cero, es decir esta muerta, entonces la actualizamos esa posicion por un cero, basicamente queda vacia
                if (matriz_vida[i][j] <= 0) {
                    mapa->grilla[i][j] = VACIO; 
                    matriz_vida[i][j] = 0;
                }
            }
        }
    }
}

// Funcion para la logica del movimiento de los zombies en el tablero
void mover_zombies(Jardin *mapa, int **matriz_vida, int *salud_casa, int turno, Config *config) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Creamos una bandera para saber si le toca moverse a este zombie en específico
            int le_toca_moverse = 0;

            // Revisamos el tipo de zombie base y si su velocidad coincide con el turno actual
            if (mapa->grilla[i][j] == ZOMBIE_BASE && (turno % config->vel_zombie_base == 0)) {
                le_toca_moverse = 1; // Actualizamos la bandera ya que el zombie puede moverse
            } 
            else if (mapa->grilla[i][j] == ZOMBIE_FLAG && (turno % config->vel_zombie_flag == 0)) {
                le_toca_moverse = 1;
            }

            // Si el zombie puede moverse
            if (le_toca_moverse==1) {
                // Este es el caso si donde se movera es a la casa
                // Ademas donde esta parado corresponde a la casa, entonces le quitamos una vida a la salud de la casa, eliminamos al zombie y actualizamos esa posicion por vacio
                if (j == 0) {
                    *salud_casa -= 1; 
                    mapa->grilla[i][j] = VACIO; 
                    matriz_vida[i][j] = 0;
                }  // Si la posicion a donde se movera el zombie es vacia
                else if (mapa->grilla[i][j - 1] == VACIO) { 
                    // Actualizamos la posicion a donde se va a mover, por el zombie, y en la posicion que estaba la actualizamos a vacia
                    mapa->grilla[i][j - 1] = mapa->grilla[i][j];
                    mapa->grilla[i][j] = VACIO;
                    // Actualizamos la vida del zombie a la posicion donde se traslado
                    matriz_vida[i][j - 1] = matriz_vida[i][j];
                    // Como el zombie se movio a una nueva posicion, la posicion en la que estaba, quedara vacia
                    matriz_vida[i][j] = 0;
                }
            }
        }
    }
}

//Funcion para generar zombies de forma aleatoria basandose en su frecuencia y oleada actual
int generar_zombies(Jardin *mapa, int **matriz_vida, Config *config, int turno, int oleada_actual, int *zombies_generados_oleada) {
    // Si ya pasamos el limite de oleadas de la configuracion, no generamos mas
    if (oleada_actual > config->max_oleadas) {
        return 0; 
    }

    // Durante el tiempo de preparacion no aparecen zombies
    if (turno <= config->t_preparacion) {
        return 0;
    }

    // Si el contador es negativo estamos en descanso entre oleadas, sube de a uno por turno hasta llegar a 0
    if (*zombies_generados_oleada < 0) {
        (*zombies_generados_oleada)++;
        return 0;
    }

    int zombies_totales_oleada = (oleada_actual * 3) + 2;
    
    // Si ya generamos todos los zombies de esta oleada, no hacemos nada más.
    if (*zombies_generados_oleada >= zombies_totales_oleada) {
        return 0;
    }

    // Verificamos si es turno de  spawnear un zombie base
    if (turno % config->frec_zombie_base == 0) {
        // Elegimos una fila azar dentro de las dimensiones del mapa
        int fila_azar = rand() % mapa->fila;
        int col_final = mapa->columna - 1; // Nos paramos en el extremo derecho, ya que los zombies atacan de derecha a izquierda

        // Revisamos si el tablero en dicha posicion esta vacio
        if (mapa->grilla[fila_azar][col_final] == VACIO) {

            // Incrementamos el contador de zombies generados
            (*zombies_generados_oleada)++;

            // Si es el zombie final de la oleada, spawneamos el zombie flag
            if (*zombies_generados_oleada == zombies_totales_oleada) {
                mapa->grilla[fila_azar][col_final] = ZOMBIE_FLAG;
                matriz_vida[fila_azar][col_final] = config->vida_zombie_flag;
                return 1; // Terminamos de generar zombies en la oleada
            } else {
                // Si no era el zombie final, generamos un zombie normal
                mapa->grilla[fila_azar][col_final] = ZOMBIE_BASE;
                matriz_vida[fila_azar][col_final] = config->vida_zombie_base;
            }
        }
    }
    return 0; // Se sigue generando la oleada
}

 // Funcion para revisar si termina o continua el juego dependiendo lo que retorne
 // 0 continua, -1 derrota por salud de la casa, 1 victoria
int revisar_fin_juego(Jardin *mapa, int salud_casa, Config *config, int oleada_actual) {

    // Revisamos los casos: 
    // Si La casa se quedo sin vida (valores menores o iguales que cero), entonces es una derrota
    if (salud_casa <= 0) {
        return -1; 
    }

    // Si pasamos el maximo de oleadas permitidas, entonces es una victoria
    if (oleada_actual > config->max_oleadas) {
        // Bandera para ver si hay zombies vivos en la oleada
        int zombies_vivos = 0;
        // Recorremos el tablero buscando si hay zombies vivos
        for (int i = 0; i < mapa->fila; i++) {
            for (int j = 0; j < mapa->columna; j++) {
                if (mapa->grilla[i][j] == ZOMBIE_BASE || mapa->grilla[i][j] == ZOMBIE_FLAG) {
                    zombies_vivos = 1;
                }
            }
        }
        // Si no hay ningun zombie vivo y las oleadas terminaron, es una victoria
        if (zombies_vivos == 0) {
            return 1; 
        }
    }
    // En el caso que no hay derrota ni victoria, el juego debe continuar
    return 0; 
}

 // Funcion para ir avanzando en los turnos/ronda de juegos, ejectuando la logica del juego en cada uno de ellos
void avanzar_turno(Jardin *mapa, int **matriz_vida, int *salud_casa, int *soles, Config *config, int *turno, int *oleada_actual, int *zombies_generados_oleada) {
    // Avanzamos al primer turno de juego
    (*turno)++;
    // Empieza a correr la logica del juego dependiendo en el caso que caiga
    ataques_plantas(mapa, matriz_vida, config, *turno);
    ataques_zombies(mapa, matriz_vida, config, *turno);
    limpiar_muertos(mapa, matriz_vida);
    mover_zombies(mapa, matriz_vida, salud_casa, *turno, config);
    gestion_soles(mapa, soles, config, *turno);

    // Generamos zombies, si sale el ultimo de la oleada (el flag) pasamos a la siguiente
    if (generar_zombies(mapa, matriz_vida, config, *turno,*oleada_actual, zombies_generados_oleada) == 1){
        // Pasamos a la siguiente oleada
        (*oleada_actual)++;
        // Empieza el descanso entre oleadas: el contador queda en negativo
        *zombies_generados_oleada = -config->t_descanso;
    }

}