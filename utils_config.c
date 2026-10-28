#include "utils_config.h"

int load_config(const char *file_route, Config *config) { // Funcion para cargar datos de config en el struct correspondiente
    FILE *file = fopen(file_route, "r");
    if (file == NULL) {
        printf("No se pudo leer archivo\n");
        return 0;
    } else if (config == NULL) {
        printf("Error de puntero a config\n");
        fclose(file);
        return 0;
    }

    char linea[100]; // Buffer para leer archivo
    char clave[50];  // Guarda nombre y compara con nombre de config
    int valor;       // Guarda valor de cada struct en config
    while (fgets(linea, sizeof(linea), file)) {
        linea[strcspn(linea, "\r\n")] = 0; // Quita saltos de linea y cursor
        if (linea[0] == '\0') {
            continue;
        }
        if (sscanf(linea, "%49[^=]=%d", clave, &valor) == 2) { // sscanf busca clave en config, y si coincide guarda el valor correspondiente
            if (strcmp(clave, "VIDA_ZOMBIE_BASE") == 0) { config->vida_zombie_base = valor;
            } else if (strcmp(clave, "VIDA_ZOMBIE_FLAG") == 0) { config->vida_zombie_flag = valor;
            } else if (strcmp(clave, "VIDA_ZOMBIE_CONO") == 0) { config->vida_zombie_cono = valor;
            } else if (strcmp(clave, "VIDA_ZOMBIE_RUGBY") == 0) { config->vida_zombie_rugby = valor;
            } else if (strcmp(clave, "VIDA_LANZAGUISANTE") == 0) { config->vida_lanzaguisante = valor;
            } else if (strcmp(clave, "VIDA_GIRASOL") == 0) { config->vida_girasol = valor;
            } else if (strcmp(clave, "VIDA_NUEZ") == 0) { config->vida_nuez = valor;
            } else if (strcmp(clave, "VIDA_HONGO") == 0) { config->vida_hongo = valor;
            } else if (strcmp(clave, "VIDA_CASA") == 0) { config->vida_casa = valor;
            } else if (strcmp(clave, "T_PREPARACION") == 0) { config->t_preparacion = valor;
            } else if (strcmp(clave, "T_DESCANSO") == 0) { config->t_descanso = valor;
            } else if (strcmp(clave, "SOL_INICIAL") == 0) { config->sol_inicial = valor;
            } else if (strcmp(clave, "VALOR_SOL") == 0) { config->valor_sol = valor;
            } else if (strcmp(clave, "COST_LANZAGUISANTE") == 0) { config->cost_lanzaguisante = valor;
            } else if (strcmp(clave, "COST_GIRASOL") == 0) { config->cost_girasol = valor;
            } else if (strcmp(clave, "COST_NUEZ") == 0) { config->cost_nuez = valor;
            } else if (strcmp(clave, "COST_JALAPENO") == 0) { config->cost_jalapeno = valor;
            } else if (strcmp(clave, "COST_HONGO") == 0) { config->cost_hongo = valor;
            } else if (strcmp(clave, "FREC_SOL_BASE") == 0) { config->frec_sol_base = valor;
            } else if (strcmp(clave, "FREC_SOL_GIRASOL") == 0) { config->frec_sol_girasol = valor;
            } else if (strcmp(clave, "FREC_LANZAGUISANTE") == 0) { config->frec_lanzaguisante = valor;
            } else if (strcmp(clave, "FREC_ZOMBIE_BASE") == 0) { config->frec_zombie_base = valor;
            } else if (strcmp(clave, "VEL_ZOMBIE_BASE") == 0) { config->vel_zombie_base = valor;
            } else if (strcmp(clave, "VEL_ZOMBIE_FLAG") == 0) { config->vel_zombie_flag = valor;
            } else if (strcmp(clave, "VEL_ZOMBIE_RUGBY") == 0) { config->vel_zombie_rugby = valor;
            } else if (strcmp(clave, "VEL_ZOMBIE_CONO") == 0) { config->vel_zombie_cono = valor;
            } else if (strcmp(clave, "DMG_LANZAGUISANTE") == 0) { config->dmg_lanzaguisante = valor;
            } else if (strcmp(clave, "DMG_JALAPENO") == 0) { config->dmg_jalapeno = valor;
            } else if (strcmp(clave, "DMG_ZOMBIE_BASE") == 0) { config->dmg_zombie_base = valor;
            } else if (strcmp(clave, "MAX_OLEADAS") == 0) { config->max_oleadas = valor;
            }
        }
    }

    fclose(file);
    return 1;
}

void print_config(const Config *config) { // Imprime los valores almacenados de config
    if (!config) {
        printf("Configuracion invalida o nula.\n");
        return;
    }

    printf("Configuracion cargada: \n");
    printf("Vida Zombie Base:      %d\n", config->vida_zombie_base);
    printf("Vida Zombie Flag:      %d\n", config->vida_zombie_flag);
    printf("Vida Zombie Cono:      %d\n", config->vida_zombie_cono);
    printf("Vida Zombie Rugby:     %d\n", config->vida_zombie_rugby);
    printf("Vida Lanzaguisante:    %d\n", config->vida_lanzaguisante);
    printf("Vida Girasol:          %d\n", config->vida_girasol);
    printf("Vida Nuez:             %d\n", config->vida_nuez);
    printf("Vida Hongo:            %d\n", config->vida_hongo);
    printf("Vida Casa:             %d\n", config->vida_casa);
    printf("Tiempo Preparacion:    %d\n", config->t_preparacion);
    printf("Tiempo Descanso:       %d\n", config->t_descanso);
    printf("Sol Inicial:           %d\n", config->sol_inicial);
    printf("Valor Sol:             %d\n", config->valor_sol);
    printf("Costo Lanzaguisante:   %d\n", config->cost_lanzaguisante);
    printf("Costo Girasol:         %d\n", config->cost_girasol);
    printf("Costo Nuez:            %d\n", config->cost_nuez);
    printf("Costo Jalapeno:        %d\n", config->cost_jalapeno);
    printf("Costo Hongo:           %d\n", config->cost_hongo);
    printf("Frecuencia Sol Base:   %d\n", config->frec_sol_base);
    printf("Frecuencia Sol Girasol:%d\n", config->frec_sol_girasol);
    printf("Frec. Lanzaguisante:   %d\n", config->frec_lanzaguisante);
    printf("Frecuencia Zombie Base:%d\n", config->frec_zombie_base);
    printf("Velocidad Zombie Base: %d\n", config->vel_zombie_base);
    printf("Velocidad Zombie Flag: %d\n", config->vel_zombie_flag);
    printf("Velocidad Zombie Cono: %d\n", config->vel_zombie_cono);
    printf("Velocidad Zombie Rugby:%d\n", config->vel_zombie_rugby);
    printf("Dano Lanzaguisante:    %d\n", config->dmg_lanzaguisante);
    printf("Dano Jalapeno:         %d\n", config->dmg_jalapeno);
    printf("Dano Zombie Base:      %d\n", config->dmg_zombie_base);
    printf("Max Oleadas:           %d\n", config->max_oleadas);
}