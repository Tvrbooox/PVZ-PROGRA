#ifndef LOGICA_H
#define LOGICA_H

#include "header.h"

// Funciones para la logica del juego
void mostrar_powerups(Jardin *mapa, Config *config);
int usar_powerup(Jardin *mapa, int f, int c, Config *config);
void patatas_explotan(Jardin *mapa);
void quemar_fila(Jardin *mapa, int f, Config *config);
int plantar(Jardin *mapa, int f, int c, Tipo_casilla tipo_planta, int *soles, Config *config);
void gestion_soles(Jardin *mapa, int *soles_jugador, Config *config, int turno);
void ataques_plantas(Jardin *mapa, Config *config, int turno);
void ataques_zombies(Jardin *mapa, int turno);
void limpiar_muertos(Jardin *mapa);
void mover_zombies(Jardin *mapa, int *salud_casa, int turno, Config *config);

// Funciones para las oleadas, fin del juego y spawn de zombies
int generar_zombies(Jardin *mapa, Config *config, int turno, int oleada_actual, int *zombies_generados_oleada);
int revisar_fin_juego(Jardin *mapa, int salud_casa, Config *config, int oleada_actual);
void avanzar_turno(Jardin *mapa, int *salud_casa, int *soles, Config *config, int *turno, int *oleada_actual, int *zombies_generados_oleada);

#endif
