#ifndef UTILS_MAP_H
#define UTILS_MAP_H

#include <stdio.h>
#include <stdlib.h>

typedef enum { // Valores para representar obj en las casillas de matriz
    VACIO = 0,   
    LANZAGUISANTE = 1,
    GIRASOL = 2,
    NUEZ = 3,
    JALAPENO = 4,
    HONGO = 5,
    ZOMBIE_BASE = 6,
    ZOMBIE_FLAG = 7,
    ZOMBIE_CONO = 8,
    ZOMBIE_RUGBY = 9
} Tipo_casilla;

typedef struct { // Elementos de matriz dinamica
    int fila;
    int columna;
    int **grilla;
} Jardin;

Jardin* load_map(const char* file_route);
void print_map(const Jardin* mapa);
void clear_map(Jardin* mapa);
void make_map(const char* file_route, int filas, int columnas);

#endif