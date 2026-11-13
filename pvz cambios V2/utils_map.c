#include "header.h"

//inicializa cada entidad
Entidad* make_entity(Tipo_casilla tipo, const Config* config) {
    if (tipo == VACIO) return NULL;

    Entidad *entity = (Entidad*)malloc(sizeof(Entidad));//reserva memoria y toma el tipo de la casilla
    entity->tipo = tipo;
    entity->acumulador = 0;//todas las entidades parten con el acumulador en 0

    switch (tipo) {//dependiendo del tipo, se aplican parametros de config
        case GIRASOL:
            entity->vida = config->vida_girasol;
            entity->vida_max = config->vida_girasol;
            entity->ataque = 0;
            entity->velocidad = 0;
            entity->frec_accion = config->frec_sol_girasol;
            entity->gen_soles = config->valor_sol;
            break;
        case LANZAGUISANTE:
            entity->vida = config->vida_lanzaguisante;
            entity->vida_max = config->vida_lanzaguisante;
            entity->ataque = config->dmg_lanzaguisante;
            entity->velocidad = 0;
            entity->frec_accion = config->frec_lanzaguisante;
            entity->gen_soles = 0;
            break;
        case NUEZ:
            entity->vida = config->vida_nuez;
            entity->vida_max = config->vida_nuez;
            entity->ataque = 0;
            entity->velocidad = 0;
            entity->frec_accion = 0;
            entity->gen_soles = 0;
            break;
        case PATATA_BOOM://la patata explota al ser pisada, frec_accion guarda los turnos que le faltan para armarse
            entity->vida = config->vida_patata;
            entity->vida_max = config->vida_patata;
            entity->ataque = config->dmg_patata;
            entity->velocidad = 0;
            entity->frec_accion = config->t_armado_patata;
            entity->gen_soles = 0;
            break;
        case JALAPENO:
            entity->vida = 0;
            entity->vida_max = 0;
            entity->ataque = 0;
            entity->velocidad = 0;
            entity->frec_accion = 0;
            entity->gen_soles = 0;
            break;
        case ZOMBIE_BASE:
            entity->vida = config->vida_zombie_base;
            entity->vida_max = config->vida_zombie_base;
            entity->ataque = config->dmg_zombie_base;
            entity->velocidad = config->vel_zombie_base;
            entity->frec_accion = 1;
            entity->gen_soles = 0;
            break;
        case ZOMBIE_FLAG:
            entity->vida = config->vida_zombie_flag;
            entity->vida_max = config->vida_zombie_flag;
            entity->ataque = config->dmg_zombie_base;
            entity->velocidad = config->vel_zombie_flag;
            entity->frec_accion = 1;
            entity->gen_soles = 0;
            break;
        case ZOMBIE_CONO:
            entity->vida = config->vida_zombie_cono;
            entity->vida_max = config->vida_zombie_cono;
            entity->ataque = config->dmg_zombie_base;
            entity->velocidad = config->vel_zombie_cono;
            entity->frec_accion = 1;
            entity->gen_soles = 0;
            break;
        case ZOMBIE_RUGBY:
            entity->vida = config->vida_zombie_rugby;
            entity->vida_max = config->vida_zombie_rugby;
            entity->ataque = config->dmg_zombie_base;
            entity->velocidad = config->vel_zombie_rugby;
            entity->frec_accion = 1;
            entity->gen_soles = 0;
            break;
        default:
            free(entity);
            return NULL;
    }
    return entity;
}

void plant(Casilla *casilla, Tipo_casilla tipo, const Config *config) {//libera espacio y guarda tipo en la casilla, para agregar parametros base
    if (casilla->planta != NULL) free(casilla->planta);
    casilla->planta = make_entity(tipo, config);
}
void add_zombie(Casilla *casilla, Tipo_casilla tipo, const Config *config) {
    if (casilla->cant_zombies >= casilla->cap_zombies) {//capacidad inicial de 2, cada vez que se llena se multiplica por 2
        casilla->cap_zombies = (casilla->cap_zombies == 0) ? 2 : casilla->cap_zombies * 2;
        casilla->zombies = (Entidad**)realloc(casilla->zombies, casilla->cap_zombies * sizeof(Entidad*));//reasigna memoria basado en la cantidad necesaria
    }
    casilla->zombies[casilla->cant_zombies] = make_entity(tipo, config);//hace que la casilla sea tipo zombie y suma 1 a cantidad de zombies
    casilla->cant_zombies++;
}

void rem_zombie(Casilla *casilla, int indice) {
    if (indice < 0 || indice >= casilla->cant_zombies) return;//revisa que el indice sea valido

    free(casilla->zombies[indice]);//libera memoria y recorre elementos para tapar hueco de zombie removido
    for (int i = indice; i < casilla->cant_zombies - 1; i++) {
        casilla->zombies[i] = casilla->zombies[i + 1];
    }
    casilla->cant_zombies--;
}

Jardin* load_map(const char* file_route, const Config* config) {
    FILE* file = fopen(file_route, "r");
    if (!file) return NULL;

    Jardin* mapa = (Jardin*)malloc(sizeof(Jardin));
    if (fscanf(file, "%d %d", &mapa->fila, &mapa->columna) != 2) {
        fclose(file);
        free(mapa);
        return NULL;
    }

    mapa->grilla = (Casilla**)malloc(mapa->fila * sizeof(Casilla*));//reserva memoria para el mapa
    for (int i = 0; i < mapa->fila; i++) {
        mapa->grilla[i] = (Casilla*)malloc(mapa->columna * sizeof(Casilla));//se inicializan los punteros como nulos
        for (int j = 0; j < mapa->columna; j++) {
            mapa->grilla[i][j].planta = NULL;
            mapa->grilla[i][j].zombies = NULL;
            mapa->grilla[i][j].cant_zombies = 0;//la cantidad y capacidad de zombies se inicializan en 0
            mapa->grilla[i][j].cap_zombies = 0;

            int val_tipo = 0;//lee el tipo de variable y planta o suma un zombie cuando la variable coincide
            fscanf(file, "%d", &val_tipo);
            if (val_tipo >= 1 && val_tipo <= 5) {
                plant(&mapa->grilla[i][j], (Tipo_casilla)val_tipo, config);
            } else if (val_tipo >= 6) {
                add_zombie(&mapa->grilla[i][j], (Tipo_casilla)val_tipo, config);
            }
        }
    }

    fclose(file);
    return mapa;
}

void print_map(const Jardin* mapa) {
    if (!mapa) return;
    printf("Mapa de %d x %d: \n", mapa->fila, mapa->columna);
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla c = mapa->grilla[i][j];
            int p_id = c.planta ? c.planta->tipo : 0;
            printf(" [%d|Z:%d] ", p_id, c.cant_zombies);
        }
        printf("\n");
    }
}

void clear_map(Jardin* mapa) {
    if (!mapa) return;
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            if (mapa->grilla[i][j].planta) free(mapa->grilla[i][j].planta);
            for (int z = 0; z < mapa->grilla[i][j].cant_zombies; z++) {
                free(mapa->grilla[i][j].zombies[z]);
            }
            if (mapa->grilla[i][j].zombies) free(mapa->grilla[i][j].zombies);
        }
        free(mapa->grilla[i]);
    }
    free(mapa->grilla);
    free(mapa);
}
