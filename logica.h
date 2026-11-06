#ifndef LOGICA_H
#define LOGICA_H

#include "utils_map.h"
#include "utils_config.h"

// Funciones para el tablero de juego y memoria
int** crear_matriz(int filas, int columnas);
void liberar_matriz(int** m, int filas);
void imprimir_matriz(int** m, int filas, int columnas);

// Funciones para la logica del juego
int plantar(Jardin *mapa, int **matriz_vida, int f, int c, Tipo_casilla tipo_planta, int *soles, Config *config);
void gestion_soles(Jardin *mapa, int *soles_jugador, Config *config, int turno);
void ataques_plantas(Jardin *mapa, int **matriz_vida, Config *config, int turno);
void ataques_zombies(Jardin *mapa, int **matriz_vida, Config *config, int turno);
void limpiar_muertos(Jardin *mapa, int **matriz_vida);
void mover_zombies(Jardin *mapa, int **matriz_vida, int *salud_casa, int turno, Config *config);

// Funciones para las oleadas, fin del juego y spawn de zombies
int generar_zombies(Jardin *mapa, int **matriz_vida, Config *config, int turno, int oleada_actual, int *zombies_generados_oleada);
int revisar_fin_juego(Jardin *mapa, int salud_casa, Config *config, int oleada_actual);
void avanzar_turno(Jardin *mapa, int **matriz_vida, int *salud_casa, int *soles, Config *config, int *turno, int *oleada_actual, int *zombies_generados_oleada);

#endif