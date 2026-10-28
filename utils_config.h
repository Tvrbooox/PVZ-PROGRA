#ifndef UTILS_CONFIG_H
#define UTILS_CONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct { // Constantes que se guardan desde config
    int vida_zombie_base;
    int vida_zombie_flag;
    int vida_zombie_cono;
    int vida_zombie_rugby;
    int vida_lanzaguisante;
    int vida_girasol;
    int vida_nuez;
    int vida_hongo;
    int vida_casa;
    int t_preparacion;
    int t_descanso;
    int sol_inicial;
    int cost_lanzaguisante;
    int cost_girasol;
    int cost_nuez;
    int cost_jalapeno;
    int cost_hongo;
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
    int dmg_zombie_base;
} Config;

int load_config(const char *file_route, Config *config);
void print_config(const Config *config);

#endif