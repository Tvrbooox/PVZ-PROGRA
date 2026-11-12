#ifndef UTILS_MAP_H
#define UTILS_MAP_H

#include "raylib.h"
#include <stdio.h>

typedef struct Guisante {
    Vector2 posicion;
    Vector2 posicionInicial;
    Vector2 velocidad;
    bool activo;
    float tiempo;
} Guisante; 

typedef struct Lanzaguisante{
    float tiempo;
    bool activo;
    int CeldaX;
    int CeldaY;
} Lanzaguisante;

void MostrarMatriz(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas, int CoordenadaX, int CoordenadaY, Color *ColoresTablero);
int ColisionesMatriz(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas,int CoordenadaX, int CoordenadaY,int Seleccionado,Vector2 mouse);
void Sol(int SolesMax,int Tamaño_Celdas,int CantidadCeldasX,Vector2 mouse,int SolesX[SolesMax], int SolesY[SolesMax], float PosicionY[SolesMax],float Tiempo);
void MostrarPlanta(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas);
void Lanzar_Guisantes(int Matriz[5][9],int Tamaño_Celdas, int ZombieEnFila[5],int MatrizConfirmacion[5][9],Lanzaguisante Lanzaguisantes[10],Guisante Guisantes[10]);

#endif