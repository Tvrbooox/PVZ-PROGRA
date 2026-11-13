#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum {
    VACIO = 0,   
    LANZAGUISANTE = 1,
    GIRASOL = 2,
    NUEZ = 3,
    JALAPENO = 4,
    PATATA_BOOM = 5,
    ZOMBIE_BASE = 6,
    ZOMBIE_FLAG = 7,
    ZOMBIE_CONO = 8,
    ZOMBIE_RUGBY = 9
} Tipo_casilla;

typedef struct { //guarda parametros del objeto
    Tipo_casilla tipo;
    int fila;
    int columna;
    int vida;
    int vida_max;
    int ataque;
    int velocidad;
    int frec_accion;
    int gen_soles;
    int acumulador; //zombies que ha eliminado el lanzaguisantes, carga su powerup
} Entidad;

typedef struct {
    Entidad *planta;//puntero para plantas
    Entidad **zombies; //matriz dinamica para zombies
    int cant_zombies;//cantidad de zombies
    int cap_zombies;//limite de zombies en una casilla
} Casilla;

typedef struct {
    int vida_zombie_base;
    int vida_zombie_flag;
    int vida_zombie_cono;
    int vida_zombie_rugby;
    int vida_lanzaguisante;
    int vida_girasol;
    int vida_nuez;
    int vida_patata;
    int vida_casa;
    int t_preparacion;
    int t_descanso;
    int sol_inicial;
    int cost_lanzaguisante;
    int cost_girasol;
    int cost_nuez;
    int cost_jalapeno;
    int cost_patata;
    int frec_sol_base;
    int frec_sol_girasol;
    int frec_lanzaguisante;
    int frec_zombie_base;
    int vel_zombie_base;
    int vel_zombie_flag;
    int vel_zombie_rugby;
    int vel_zombie_cono;
    int max_oleadas;
    int valor_sol;
    int dmg_lanzaguisante;
    int dmg_jalapeno;
    int dmg_patata;
    int t_armado_patata;
    int kills_powerup;
    int dmg_powerup;
    int dmg_zombie_base;
} Config;

typedef struct {
    int fila;
    int columna;
    Casilla **grilla;
} Jardin;

//prototipos funciones
Entidad* make_entity(Tipo_casilla tipo, const Config* config);
void plant(Casilla *casilla, Tipo_casilla tipo, const Config *config);
void add_zombie(Casilla *casilla, Tipo_casilla tipo, const Config *config);
void rem_zombie(Casilla *casilla, int indice);
int load_config(const char *file_route, Config *config);
Jardin* load_map(const char* file_route, const Config* config);
void print_map(const Jardin* mapa);
void clear_map(Jardin* mapa);
void make_map(const char* file_route, int filas, int columnas);
void print_config(const Config* config);

#endif
