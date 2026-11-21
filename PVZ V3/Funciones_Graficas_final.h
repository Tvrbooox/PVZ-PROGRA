#ifndef UTILS_MAP_H
#define UTILS_MAP_H

#include "raylib.h"
#include <stdio.h>
#include "header.h"

typedef struct Guisante {
    Vector2 posicion;
    Vector2 posicionInicial;
    Vector2 velocidad;
    bool activo;
    float tiempo;
    Rectangle Colision;
} Guisante; 

typedef struct Lanzaguisante{
    float tiempo;
    bool activo;
    int CeldaX;
    int CeldaY;
    int Vida;
    Rectangle Colision;
    Rectangle ColisionLanzar;
    bool Mejora;
    float TiempoMejora;
} Lanzaguisante;

typedef struct Girasol{
    float tiempo;
    int CoordX;
    int CoordY;
    bool activo;
    int Vida;
    Rectangle Colision;
    bool Mejora;
} Girasol;

typedef struct GirasolSol{
    int CoordX;
    int CoordY;
    bool activo;
} GirasolSol;

typedef struct Sol{
    int FinalX;
    int FinalY;
    float Posicion;
    float activo;
} Sol;

typedef struct ZombieGrafico{
    bool Activo;
    int Fila;
    float PosicionX;
    int Tipo;
    int Vida;
    int Velocidad;
    Rectangle Colision;
    Texture2D ColorZombie;
    int Daño;
    bool Detenerse;
    float TiempoGolpe;
    int Interactuando;
} ZombieGrafico;

typedef struct Nuez{
    int Vida;
    bool Activo;
    Rectangle Colision;
    int Fila;
    int Columna;
} Nuez;

typedef struct Patata{
    bool Activo;
    bool ExplosionActiva;
    int Fila;
    int Columna;
    int Vida;
    Rectangle Colision;
    Rectangle ColisionExplosion;
    float Tiempo;
    int Daño;
    Texture2D Sprite;
    bool ExplosionSprite;
    float TiempoSprite;
} Patata;

typedef struct Jalapeno{
    bool Activo;
    int Fila;
    int Columna;
    int Vida;
    Rectangle Colision;
    float Tiempo;
    int Daño;
} Jalapeno;

typedef struct FuegoJalapeno{
    bool Activo;
    float Tiempo;
    Rectangle Colision;
    int Fila;
} FuegoJalapeno;

void MostrarMatriz(int CoordXInicio, int CoordYInicio, int NumFilas, int NumColumnas, int Tamaño_CeldasX, int Tamaño_CeldasY, Texture2D Pasto[2]);
int ColisionesMatriz(int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY, int Alto, int Ancho, int Matriz[Alto][Ancho], int Seleccionado, Vector2 mouse, int *SolesActuales, int Valor[6], Sound plant);
void GenerarSol(int MaxEntidades, Sol Soles[MaxEntidades], Vector2 mouse, float TiempoSoles, int *SolesActuales, int ValorSol, Texture2D SolSprite, Sound Sonido);
void MostrarPlanta(int MaxEntidades, int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY, int Alto, int Ancho, int Matriz[Alto][Ancho], Texture2D GirasolSprite, Texture2D LanzaguisanteSprite, Texture2D NuezSprite, Texture2D JalapenoSprite, Patata Patatas[MaxEntidades], Texture2D LanzaguisanteMejoraSprite, Texture2D GirasolMejoraSprite);
void Lanzar_Guisantes(int MaxEntidades, int NumFilas, int NumColumnas, int Tamaño_CeldasX, int Tamaño_CeldasY, int MatrizConfirmacion[NumFilas][NumColumnas], Lanzaguisante Lanzaguisantes[10], Guisante Guisantes[10], ZombieGrafico Zombies[20], Texture2D Guisante, Sound Sonido);
void Generador_SolesGirasol(int MaxEntidades, Girasol Girasoles[MaxEntidades], GirasolSol GirasolSoles[MaxEntidades], Vector2 mouse, int Tamaño_CeldasX, int Tamaño_CeldasY, int CoordXInicio, int CoordYInicio, int *SolesActuales, int ValorSol, Texture2D SolSprite, Sound Sonidos);
void ColisionPlantaZombie(bool *PlantaActivo, Rectangle *PlantaColision, int *PlantaVida, int *PlantaCoordX, int *PlantaCoordY, int NumFilas, int NumColumnas, int MatrizNueva[NumFilas][NumColumnas], int MatrizConfirmacion[NumFilas][NumColumnas], ZombieGrafico Zombies[20], int i, int Identificador, Sound Mordida);
int OrdenarParametros(int iFilas, int jColumnas, bool *PlantaActivo, int *PlantaVida, Rectangle *PlantaColision, int *PlantaCoordX, int *PlantaCoordY, int Ancho, int Alto, int Tamaño_CeldasX, int Tamaño_CeldasY, int CoordXInicio, int CoordYInicio, int Vida);
void Matriz_Ceros(int NumFilas, int NumColumnas, int Matriz[NumFilas][NumColumnas]);
void ConfigurarPlantas(int MaxEntidades, int NumFilas, int NumColumnas, int MatrizNueva[NumFilas][NumColumnas], int MatrizNueces[NumFilas][NumColumnas], int Tamaño_CeldasX, int Tamaño_CeldasY, int CoordXInicio, int CoordYInicio, Nuez Nueces[MaxEntidades], int MatrizLanzaguisantes[NumFilas][NumColumnas], Lanzaguisante Lanzaguisantes[MaxEntidades], int MatrizGirasoles[NumFilas][NumColumnas], Girasol Girasoles[MaxEntidades], int MatrizJalapenos[NumFilas][NumColumnas], Jalapeno Jalapenos[MaxEntidades], int MatrizPatatas[NumFilas][NumColumnas], Patata Patatas[MaxEntidades], Config *config);
int Menu(Music TemaMenu);
void ColisionTienda(Vector2 mouse, int *Seleccionado, Texture2D Compra[7], Texture2D SeleccionadoSprite);
void ConfigurarZombie(Jardin *mapa, ZombieGrafico Zombies[20], Config *config, Texture2D ZombieSprite, Texture2D FlagZombieSprite, Texture2D FootballZombie, int CoordYInicio, int Tamaño_CeldasY);
void ZombieMuerto(ZombieGrafico Zombies[20]);
void ColisionesGuisante(int MaxEntidades, ZombieGrafico Zombies[20], Guisante Guisantes[MaxEntidades], Config *config, Sound Sonido);
void ColisionesJalapenos(int MaxEntidades, Jalapeno Jalapenos[MaxEntidades], FuegoJalapeno FuegoJalapenos[MaxEntidades], int NumFila, int NumColumna, int MatrizNueva[NumFila][NumColumna], int MatrizJalapenos[NumFila][NumColumna], Sound Sonido);
void DibujarFuegoJalapeno(int MaxEntidades, FuegoJalapeno FuegoJalapenos[MaxEntidades], int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY, Texture2D FuegoJalapenoSprite, int NumColumnas);
void ColisionFuegoJalapenos(int MaxEntidades, ZombieGrafico Zombies[20], FuegoJalapeno FuegoJalapenos[MaxEntidades]);
void ColisionPatata(int MaxEntidades, Patata Patatas[MaxEntidades], ZombieGrafico Zombies[20], Texture2D ExplosionSprite, int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY, Sound Sonido);

int leer_dimensiones_partida(const char *ruta, int *filas, int *columnas);
int guardar_partida(const char *ruta, int soles, int salud_casa, int turno, int oleada_actual, int zombies_generados_oleada, int NumFilas, int NumColumnas, int MatrizNueva[NumFilas][NumColumnas]);
Jardin *cargar_partida(const char *ruta, const Config *config, int *soles, int *salud_casa, int *turno, int *oleada_actual, int *zombies_generados_oleada, int NumFilas, int NumColumnas, int MatrizNueva[NumFilas][NumColumnas]);
int guardar_zombies(const char *ruta, ZombieGrafico Zombies[20]);
int cargar_zombies(const char *ruta, ZombieGrafico Zombies[20], Config *config, Texture2D ZombieSprite, Texture2D FlagZombieSprite, Texture2D FootballZombie, int NumFilas, int CoordYInicio, int Tamaño_CeldasY);
void LimpiarPartida(int NumFilas, int NumColumnas, int MatrizNueces[NumFilas][NumColumnas], int MatrizLanzaguisantes[NumFilas][NumColumnas], int MatrizGirasoles[NumFilas][NumColumnas], int MatrizJalapenos[NumFilas][NumColumnas], int MatrizPatatas[NumFilas][NumColumnas], int MatrizConfirmacion[NumFilas][NumColumnas], Nuez Nueces[10], Lanzaguisante Lanzaguisantes[10], Girasol Girasoles[10], Jalapeno Jalapenos[10], Patata Patatas[10], Guisante Guisantes[10], FuegoJalapeno FuegoJalapenos[10], Sol Soles[10], GirasolSol GirasolSoles[10]);
void LimpiarZombies(ZombieGrafico Zombies[20]);

#endif
