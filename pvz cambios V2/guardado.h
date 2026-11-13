#ifndef GUARDADO_H
#define GUARDADO_H

#include "header.h"

// Guarda el estado de la partida en un archivo de texto, retorna 1 si se pudo y 0 si no
int guardar_partida(const char *ruta, Jardin *mapa, int soles, int salud_casa, int turno, int oleada_actual, int zombies_generados_oleada);

// Carga una partida guardada, retorna el mapa nuevo (o NULL si el archivo no existe o esta danado)
// Las variables del juego quedan guardadas en los punteros que se le pasan
Jardin* cargar_partida(const char *ruta, const Config *config, int *soles, int *salud_casa, int *turno, int *oleada_actual, int *zombies_generados_oleada);

#endif
