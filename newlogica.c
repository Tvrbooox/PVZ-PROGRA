#include "logica.h"
#include <stdlib.h>
#include <stdio.h>

// Funcion para plantar en el mapa
// Mapa es el tablero(Jardin), f y c (Filas y columnas donde plantaremos), la vida de la planta la pone plant() desde la configuracion
int plantar(Jardin *mapa, int f, int c, Tipo_casilla tipo_planta, int *soles, Config *config) {

     // Condicional para no saltarnos los limites del juego
    if (f < 0 || f >= mapa->fila || c < 0 || c >= mapa->columna) {
        printf("Error: Posicion invalida.\n");
        return 0;
    }
    // Condicional en caso de que la casilla donde queramos plantar este ocupada (con una planta o con zombies)
    if (mapa->grilla[f][c].planta != NULL || mapa->grilla[f][c].cant_zombies > 0) {
        printf("Error: La casilla ya esta ocupada.\n");
        return 0; 
    }
    // Costo de la planta elegida
    int costo = 0;

    // Definimos cada personaje del juego entorno a los valores del struct
    if (tipo_planta == GIRASOL) {
        costo = config->cost_girasol; // Esto se lee como anda a donde apunta config y toma el valor de costo de girasol, y asi con cada personaje
    } else if (tipo_planta == LANZAGUISANTE) {
        costo = config->cost_lanzaguisante;
    } else if (tipo_planta == NUEZ) {
        costo = config->cost_nuez;
    }else{
        printf("Error: Tipo de planta invalido.\n");
        return 0;
    }

    // Verificamos si los soles que tenemos nos permite comprar la planta, si es asi, quitamos del total
    if (*soles >= costo) {
        *soles -= costo;
        // Creamos la planta en la casilla, con la vida que le corresponde segun la configuracion
        plant(&mapa->grilla[f][c], tipo_planta, config);
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
    }
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Si la casilla que estamos viendo tiene un girasol
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta != NULL && planta->tipo == GIRASOL) {
                // Revisa independientemente si coincide con el ciclo de produccion de los girasoles.
                if (turno % config->frec_sol_girasol== 0) {
                    //entonces le sumamos la cantidad de soles que nos brinda el girasol
                    *soles_jugador += config->valor_sol;
                } 
            }
        }
    }
}

// Funcion para gestionar el ataque de las plantas
void ataques_plantas(Jardin *mapa, Config *config, int turno) {
   // Si el turno actual no es múltiplo de la frecuencia de disparo, sale de la funcion inmediatamente 
    //  Los lanzaguisantes recargan en los turnos restantes, la idea del resto nos ayuda a forzar los turnos en los multiplos de la frecuencia
    if (turno % config->frec_lanzaguisante!= 0) {
        return; 
    }
    // Recorre cada posicion del tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            // Si la casilla tiene un lanzaguisantes
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta != NULL && planta->tipo == LANZAGUISANTE) {
                // Vemos una columna mas adelante (Derecha) para ver si hay algun zombie en esa casilla
                for (int k = j + 1; k < mapa->columna; k++) {
                    Casilla *casilla = &mapa->grilla[i][k];
                    // Si la casilla tiene zombies (base o bandera)
                    if (casilla->cant_zombies > 0) {
                        // Le quita el daño estipulado por el lanzaguisantes al primer zombie mediante lo establecido en la configuracion
                        casilla->zombies[0]->vida -= config->dmg_lanzaguisante; // Actualizamos la vida del zombie restandole el dano causado por el lanzaguisantes
                        break; 
                    }
                }
            }
        }
    }
}

// Funcion para gestionas el ataque de los zombies
void ataques_zombies(Jardin *mapa, int turno) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 1; j < mapa->columna; j++) { 
            // Revisamos si a la izquierda de esta casilla hay una planta, si no hay nadie ataca
            Entidad *planta = mapa->grilla[i][j-1].planta;
            if (planta == NULL) {
                continue;
            }

            // Cada zombie de la casilla puede atacar a la planta
            for (int k = 0; k < mapa->grilla[i][j].cant_zombies; k++) {
                Entidad *zombie = mapa->grilla[i][j].zombies[k];
                // Variable bandera para controlar los ataques del zombie
                int le_toca_atacar = 0;

                // Cada zombie trae su velocidad, asi sirve para todos los tipos. Si su turno actual coincide con su velocidad de ataque
                if (turno % zombie->velocidad == 0) {
                    //Actualizamos la bandera, para que el zombie pueda atacar a la planta adyacente
                    le_toca_atacar = 1;
                }

                // Si el zombie puede atacar, el zombie ataca quitando el dano que trae guardado a la planta
                if (le_toca_atacar == 1) {
                    planta->vida -= zombie->ataque;
                }
            }
        }
    }
}

// Funcion para limpiar entidades, que han muerto
void limpiar_muertos(Jardin *mapa) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla *casilla = &mapa->grilla[i][j];

            // Si hay una planta y su vida es menor o igual que cero, es decir esta muerta, la eliminamos y la casilla queda sin planta
            if (casilla->planta != NULL && casilla->planta->vida <= 0) {
                free(casilla->planta);
                casilla->planta = NULL;
            }

            // Recorremos los zombies de atras para adelante, porque al eliminar uno los demas se corren
            for (int k = casilla->cant_zombies - 1; k >= 0; k--) {
                if (casilla->zombies[k]->vida <= 0) {
                    rem_zombie(casilla, k);
                }
            }
        }
    }
}

// Funcion para la logica del movimiento de los zombies en el tablero
void mover_zombies(Jardin *mapa, int *salud_casa, int turno, Config *config) {
    // Recorremos el tablero de juego
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla *casilla = &mapa->grilla[i][j];

            // Recorremos los zombies de atras para adelante, porque al mover uno los demas se corren
            for (int k = casilla->cant_zombies - 1; k >= 0; k--) {
                Entidad *zombie = casilla->zombies[k];
                // Creamos una bandera para saber si le toca moverse a este zombie en especifico
                int le_toca_moverse = 0;

                // Revisamos si la velocidad del zombie (la trae guardada) coincide con el turno actual
                if (turno % zombie->velocidad == 0) {
                    le_toca_moverse = 1; // Actualizamos la bandera ya que el zombie puede moverse
                }

                // Si el zombie puede moverse
                if (le_toca_moverse == 1) {
                    // Este es el caso si donde se movera es a la casa
                    // Ademas donde esta parado corresponde a la casa, entonces le quitamos una vida a la salud de la casa y eliminamos al zombie
                    if (j == 0) {
                        *salud_casa -= 1; 
                        rem_zombie(casilla, k);
                    }  // Si a la casilla donde se movera no hay una planta (los zombies si pueden compartir casilla)
                    else if (mapa->grilla[i][j - 1].planta == NULL) { 
                        Casilla *destino = &mapa->grilla[i][j - 1];
                        int antes = destino->cant_zombies;
                        // Creamos al zombie en la casilla de la izquierda y le copiamos la vida que tenia
                        add_zombie(destino, zombie->tipo, config);
                        // Solo si se pudo agregar, lo eliminamos de la casilla donde estaba
                        if (destino->cant_zombies > antes) {
                            destino->zombies[destino->cant_zombies - 1]->vida = zombie->vida;
                            rem_zombie(casilla, k);
                        }
                    }
                }
            }
        }
    }
}

//Funcion para generar zombies de forma aleatoria basandose en su frecuencia y oleada actual (base, cono desde la oleada 3, rugby desde la 5 y flag al final)
int generar_zombies(Jardin *mapa, Config *config, int turno, int oleada_actual, int *zombies_generados_oleada) {
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
    
    // Si ya generamos todos los zombies de esta oleada, no hacemos nada mas
    if (*zombies_generados_oleada >= zombies_totales_oleada) {
        return 0;
    }

    // Verificamos si es turno de  spawnear un zombie base
    if (turno % config->frec_zombie_base == 0) {
        // Elegimos una fila azar dentro de las dimensiones del mapa
        int fila_azar = rand() % mapa->fila;
        int col_final = mapa->columna - 1; // Nos paramos en el extremo derecho, ya que los zombies atacan de derecha a izquierda
        Casilla *casilla = &mapa->grilla[fila_azar][col_final];

        // El zombie final de la oleada es el zombie flag, los demas son zombies base
        int es_el_ultimo = (*zombies_generados_oleada + 1 == zombies_totales_oleada);
        int numero = *zombies_generados_oleada + 1; // numero del zombie dentro de la oleada
        Tipo_casilla tipo = ZOMBIE_BASE;
        if (es_el_ultimo) {
            tipo = ZOMBIE_FLAG;
        } else if (oleada_actual >= 5 && numero % 4 == 0) {
            tipo = ZOMBIE_RUGBY; // desde la oleada 5, cada 4 zombies sale un rugby
        } else if (oleada_actual >= 3 && numero % 3 == 0) {
            tipo = ZOMBIE_CONO; // desde la oleada 3, cada 3 zombies sale un cono
        }

        // Spawneamos solo si en esa casilla no hay una planta
        if (casilla->planta == NULL) {
            int antes = casilla->cant_zombies;
            add_zombie(casilla, tipo, config);
            // Si el zombie se agrego, incrementamos el contador de zombies generados
            if (casilla->cant_zombies > antes) {
                (*zombies_generados_oleada)++;
                if (es_el_ultimo) {
                    return 1; // Terminamos de generar zombies en la oleada
                }
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
                if (mapa->grilla[i][j].cant_zombies > 0) {
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
void avanzar_turno(Jardin *mapa, int *salud_casa, int *soles, Config *config, int *turno, int *oleada_actual, int *zombies_generados_oleada) {
    // Avanzamos al primer turno de juego
    (*turno)++;
    // Empieza a correr la logica del juego dependiendo en el caso que caiga
    ataques_plantas(mapa, config, *turno);
    ataques_zombies(mapa, *turno);
    limpiar_muertos(mapa);
    mover_zombies(mapa, salud_casa, *turno, config);
    gestion_soles(mapa, soles, config, *turno);

    // Generamos zombies, si sale el ultimo de la oleada (el flag) pasamos a la siguiente
    if (generar_zombies(mapa, config, *turno, *oleada_actual, zombies_generados_oleada) == 1){
        // Pasamos a la siguiente oleada
        (*oleada_actual)++;
        // Empieza el descanso entre oleadas: el contador queda en negativo
        *zombies_generados_oleada = -config->t_descanso;
    }
}