#include "logica.h"
#include <stdlib.h>
#include <stdio.h>

// Las cantidades de zombies del config estan pensadas para un mapa de 5 filas
#define FILAS_BASE 5

// Funcion para el jalapeño: le quita vida a todos los zombies de la fila f
void quemar_fila(Jardin *mapa, int f, Config *config) {
    for (int j = 0; j < mapa->columna; j++) {
        Casilla *casilla = &mapa->grilla[f][j];
        for (int k = 0; k < casilla->cant_zombies; k++) {
            casilla->zombies[k]->vida -= config->dmg_jalapeno;
        }
    }
}

// Funcion para plantar en el mapa
int plantar(Jardin *mapa, int f, int c, Tipo_casilla tipo_planta, int *soles, Config *config) {
    if (f < 0 || f >= mapa->fila || c < 0 || c >= mapa->columna) {
        printf("Error: Posicion invalida.\n");
        return 0;
    }
    if (mapa->grilla[f][c].planta != NULL || mapa->grilla[f][c].cant_zombies > 0) {
        printf("Error: La casilla ya esta ocupada.\n");
        return 0;
    }

    int costo = 0;
    if (tipo_planta == GIRASOL) {
        costo = config->cost_girasol;
    } else if (tipo_planta == LANZAGUISANTE) {
        costo = config->cost_lanzaguisante;
    } else if (tipo_planta == NUEZ) {
        costo = config->cost_nuez;
    } else if (tipo_planta == PATATA_BOOM) {
        costo = config->cost_patata;
    } else if (tipo_planta == JALAPENO) {
        costo = config->cost_jalapeno;
    } else {
        printf("Error: Tipo de planta invalido.\n");
        return 0;
    }

    if (*soles >= costo) {
        *soles -= costo;
        if (tipo_planta == JALAPENO) {
            quemar_fila(mapa, f, config);
        } else {
            plant(&mapa->grilla[f][c], tipo_planta, config);
        }
        return 1;
    } else {
        printf("Error: No tienes suficientes soles.\n");
        return 0;
    }
}

// Funcion para ir gestionando la cantidad de soles que tiene el jugador
void gestion_soles(Jardin *mapa, int *soles_jugador, Config *config, int turno) {
    if (config->frec_sol_base > 0 && turno % config->frec_sol_base == 0) {
        *soles_jugador += config->valor_sol;
    }

    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta != NULL && planta->tipo == GIRASOL) {
                if (config->frec_sol_girasol > 0 && turno % config->frec_sol_girasol == 0) {
                    *soles_jugador += config->valor_sol;
                }
            }
        }
    }
}

// Funcion para gestionar el ataque de las plantas
void ataques_plantas(Jardin *mapa, Config *config, int turno) {
    if (config->frec_lanzaguisante <= 0 || turno % config->frec_lanzaguisante != 0) {
        return;
    }

    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta != NULL && planta->tipo == LANZAGUISANTE) {
                for (int k = j + 1; k < mapa->columna; k++) {
                    Casilla *casilla = &mapa->grilla[i][k];
                    if (casilla->cant_zombies > 0) {
                        Entidad *zombie = casilla->zombies[0];
                        int vida_antes = zombie->vida;
                        zombie->vida -= config->dmg_lanzaguisante;
                        if (vida_antes > 0 && zombie->vida <= 0 && planta->acumulador < config->kills_powerup) {
                            planta->acumulador++;
                        }
                        break;
                    }
                }
            }
        }
    }
}

// Funcion para mostrar el acumulador del powerup de cada lanzaguisantes
void mostrar_powerups(Jardin *mapa, Config *config) {
    int hay_lanzaguisantes = 0;
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta != NULL && planta->tipo == LANZAGUISANTE) {
                if (hay_lanzaguisantes == 0) {
                    printf("Powerups: ");
                    hay_lanzaguisantes = 1;
                }
                if (planta->acumulador >= config->kills_powerup) {
                    printf("(%d,%d) LISTO  ", i, j);
                } else {
                    printf("(%d,%d) %d/%d  ", i, j, planta->acumulador, config->kills_powerup);
                }
            }
        }
    }
    if (hay_lanzaguisantes == 1) {
        printf("\n");
    }
}

// Funcion para usar el powerup del lanzaguisantes
int usar_powerup(Jardin *mapa, int f, int c, Config *config) {
    if (f < 0 || f >= mapa->fila || c < 0 || c >= mapa->columna) {
        printf("Error: Posicion invalida.\n");
        return 0;
    }
    Entidad *planta = mapa->grilla[f][c].planta;
    if (planta == NULL || planta->tipo != LANZAGUISANTE) {
        printf("Error: En esa casilla no hay un lanzaguisantes.\n");
        return 0;
    }
    if (planta->acumulador < config->kills_powerup) {
        printf("Error: El powerup todavia no esta cargado (%d/%d).\n", planta->acumulador, config->kills_powerup);
        return 0;
    }

    for (int j = c + 1; j < mapa->columna; j++) {
        for (int k = 0; k < mapa->grilla[f][j].cant_zombies; k++) {
            mapa->grilla[f][j].zombies[k]->vida -= config->dmg_powerup;
        }
    }
    planta->acumulador = 0;
    return 1;
}

// Funcion para la patata boom
void patatas_explotan(Jardin *mapa) {
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Entidad *planta = mapa->grilla[i][j].planta;
            if (planta == NULL || planta->tipo != PATATA_BOOM) {
                continue;
            }

            if (planta->frec_accion > 0) {
                planta->frec_accion--;
                continue;
            }

            if (j + 1 < mapa->columna && mapa->grilla[i][j + 1].cant_zombies > 0) {
                for (int f = i - 1; f <= i + 1; f++) {
                    for (int c = j; c <= j + 2; c++) {
                        if (f < 0 || f >= mapa->fila || c >= mapa->columna) {
                            continue;
                        }
                        for (int k = 0; k < mapa->grilla[f][c].cant_zombies; k++) {
                            mapa->grilla[f][c].zombies[k]->vida -= planta->ataque;
                        }
                    }
                }
                free(planta);
                mapa->grilla[i][j].planta = NULL;
            }
        }
    }
}

// Funcion para gestionar el ataque de los zombies
void ataques_zombies(Jardin *mapa, int turno) {
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 1; j < mapa->columna; j++) {
            Entidad *planta = mapa->grilla[i][j - 1].planta;
            if (planta == NULL) {
                continue;
            }

            for (int k = 0; k < mapa->grilla[i][j].cant_zombies; k++) {
                Entidad *zombie = mapa->grilla[i][j].zombies[k];
                int le_toca_atacar = 0;

                if (zombie->velocidad > 0 && turno % zombie->velocidad == 0) {
                    le_toca_atacar = 1;
                }

                if (le_toca_atacar == 1) {
                    planta->vida -= zombie->ataque;
                }
            }
        }
    }
}

// Funcion para limpiar entidades que han muerto
void limpiar_muertos(Jardin *mapa) {
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla *casilla = &mapa->grilla[i][j];

            if (casilla->planta != NULL && casilla->planta->vida <= 0) {
                free(casilla->planta);
                casilla->planta = NULL;
            }

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
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla *casilla = &mapa->grilla[i][j];

            for (int k = casilla->cant_zombies - 1; k >= 0; k--) {
                Entidad *zombie = casilla->zombies[k];
                int le_toca_moverse = 0;

                if (zombie->velocidad > 0 && turno % zombie->velocidad == 0) {
                    le_toca_moverse = 1;
                }

                if (le_toca_moverse == 1) {
                    if (j == 0) {
                        *salud_casa -= 1;
                        rem_zombie(casilla, k);
                    } else if (mapa->grilla[i][j - 1].planta == NULL) {
                        Casilla *destino = &mapa->grilla[i][j - 1];
                        int antes = destino->cant_zombies;
                        add_zombie(destino, zombie->tipo, config);
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

// Funcion para generar zombies segun frecuencia, oleada y tamaño del mapa
int generar_zombies(Jardin *mapa, Config *config, int turno, int oleada_actual, int *zombies_generados_oleada) {
    if (oleada_actual > config->max_oleadas) {
        return 0;
    }

    if (turno <= config->t_preparacion) {
        return 0;
    }

    if (*zombies_generados_oleada < 0) {
        (*zombies_generados_oleada)++;
        return 0;
    }

    int zombies_totales_oleada = (config->zombies_inicio + (oleada_actual * config->zombies_por_oleada)) * mapa->fila / FILAS_BASE;
    if (zombies_totales_oleada < 1) {
        zombies_totales_oleada = 1;
    }

    if (*zombies_generados_oleada >= zombies_totales_oleada) {
        return 0;
    }

    if (config->frec_zombie_base > 0 && turno % config->frec_zombie_base == 0) {
        int fila_azar = rand() % mapa->fila;
        int col_final = mapa->columna - 1;
        Casilla *casilla = &mapa->grilla[fila_azar][col_final];

        int es_el_ultimo = (*zombies_generados_oleada + 1 == zombies_totales_oleada);
        int numero = *zombies_generados_oleada + 1;
        Tipo_casilla tipo = ZOMBIE_BASE;
        if (es_el_ultimo) {
            tipo = ZOMBIE_FLAG;
        } else if (oleada_actual >= config->oleada_rugby && numero % 4 == 0) {
            tipo = ZOMBIE_RUGBY;
        } else if (oleada_actual >= config->oleada_cono && numero % 3 == 0) {
            tipo = ZOMBIE_CONO;
        }

        if (casilla->planta == NULL) {
            int antes = casilla->cant_zombies;
            add_zombie(casilla, tipo, config);
            if (casilla->cant_zombies > antes) {
                (*zombies_generados_oleada)++;
                if (es_el_ultimo) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Funcion para revisar si termina o continua el juego
int revisar_fin_juego(Jardin *mapa, int salud_casa, Config *config, int oleada_actual) {
    if (salud_casa <= 0) {
        return -1;
    }

    if (oleada_actual > config->max_oleadas) {
        int zombies_vivos = 0;
        for (int i = 0; i < mapa->fila; i++) {
            for (int j = 0; j < mapa->columna; j++) {
                if (mapa->grilla[i][j].cant_zombies > 0) {
                    zombies_vivos = 1;
                }
            }
        }
        if (zombies_vivos == 0) {
            return 1;
        }
    }
    return 0;
}

// Funcion para avanzar de turno en la logica del mapa
void avanzar_turno(Jardin *mapa, int *salud_casa, int *soles, Config *config, int *turno, int *oleada_actual, int *zombies_generados_oleada) {
    (*turno)++;
    ataques_plantas(mapa, config, *turno);
    ataques_zombies(mapa, *turno);
    patatas_explotan(mapa);
    limpiar_muertos(mapa);
    mover_zombies(mapa, salud_casa, *turno, config);
    gestion_soles(mapa, soles, config, *turno);

    if (generar_zombies(mapa, config, *turno, *oleada_actual, zombies_generados_oleada) == 1) {
        (*oleada_actual)++;
        *zombies_generados_oleada = -config->t_descanso;
    }
}
