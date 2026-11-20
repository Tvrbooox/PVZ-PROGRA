#include "guardado.h"

// Formato del archivo:
// linea 1: turno oleada zombies_generados soles salud_casa
// linea 2: filas columnas
// luego una linea por cada casilla que tenga algo: fila columna tipo_planta vida_planta acumulador_planta cant_zombies (tipo vida) de cada zombie
int guardar_partida(const char *ruta, Jardin *mapa, int soles, int salud_casa, int turno, int oleada_actual, int zombies_generados_oleada) {
    FILE *file = fopen(ruta, "w");
    if (file == NULL) {
        return 0;
    }

    // Guardamos las variables del juego y el tamaño del mapa
    fprintf(file, "%d %d %d %d %d\n", turno, oleada_actual, zombies_generados_oleada, soles, salud_casa);
    fprintf(file, "%d %d\n", mapa->fila, mapa->columna);

    // Recorremos el tablero y guardamos solo las casillas que tengan una planta o zombies
    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {
            Casilla *casilla = &mapa->grilla[i][j];
            if (casilla->planta == NULL && casilla->cant_zombies == 0) {
                continue;
            }

            fprintf(file, "%d %d ", i, j);
            // Si no hay planta guardamos 0 0 0
            if (casilla->planta != NULL) {
                fprintf(file, "%d %d %d ", casilla->planta->tipo, casilla->planta->vida, casilla->planta->acumulador);
            } else {
                fprintf(file, "0 0 0 ");
            }
            // Guardamos cuantos zombies hay y el tipo y la vida de cada uno
            fprintf(file, "%d", casilla->cant_zombies);
            for (int k = 0; k < casilla->cant_zombies; k++) {
                fprintf(file, " %d %d", casilla->zombies[k]->tipo, casilla->zombies[k]->vida);
            }
            fprintf(file, "\n");
        }
    }

    fclose(file);
    return 1;
}

Jardin* cargar_partida(const char *ruta, const Config *config, int *soles, int *salud_casa, int *turno, int *oleada_actual, int *zombies_generados_oleada) {
    FILE *file = fopen(ruta, "r");
    if (file == NULL) {
        return NULL;
    }

    // Leemos primero las variables y el tamaño en variables auxiliares, para no cambiar el juego si el archivo esta malo
    int t, o, z, s, h, filas, columnas;
    if (fscanf(file, "%d %d %d %d %d", &t, &o, &z, &s, &h) != 5 ||
        fscanf(file, "%d %d", &filas, &columnas) != 2 ||
        filas <= 0 || columnas <= 0) {
        fclose(file);
        return NULL;
    }

    // Creamos el mapa vacio (calloc deja planta en NULL y cantidad de zombies en 0)
    Jardin *mapa = malloc(sizeof(Jardin));
    if (mapa == NULL) {
        fclose(file);
        return NULL;
    }
    mapa->fila = 0;
    mapa->columna = columnas;
    mapa->grilla = calloc(filas, sizeof(Casilla*));
    if (mapa->grilla == NULL) {
        free(mapa);
        fclose(file);
        return NULL;
    }
    for (int i = 0; i < filas; i++) {
        mapa->grilla[i] = calloc(columnas, sizeof(Casilla));
        if (mapa->grilla[i] == NULL) {
            clear_map(mapa); // libera solo las filas que se alcanzaron a crear
            fclose(file);
            return NULL;
        }
        mapa->fila++;
    }

    // Leemos cada casilla guardada y volvemos a crear sus plantas y zombies
    int error = 0;
    int leidos;
    int f, c, tipo_planta, vida_planta, acumulador_planta, cant;
    while ((leidos = fscanf(file, "%d %d %d %d %d %d", &f, &c, &tipo_planta, &vida_planta, &acumulador_planta, &cant)) == 6 && !error) {
        // Revisamos que los datos tengan sentido
        if (f < 0 || f >= filas || c < 0 || c >= columnas || cant < 0 || tipo_planta < 0 || tipo_planta > 5) {
            error = 1;
            break;
        }
        Casilla *casilla = &mapa->grilla[f][c];

        // Creamos la planta y le ponemos la vida y el acumulador que tenia guardados
        if (tipo_planta >= 1) {
            plant(casilla, (Tipo_casilla)tipo_planta, config);
            if (casilla->planta != NULL) {
                casilla->planta->vida = vida_planta;
                casilla->planta->acumulador = acumulador_planta;
            }
        }

        // Creamos cada zombie y le ponemos la vida que tenia guardada
        for (int k = 0; k < cant && !error; k++) {
            int tipo_zombie, vida_zombie;
            if (fscanf(file, "%d %d", &tipo_zombie, &vida_zombie) != 2 || tipo_zombie < 6 || tipo_zombie > 9) {
                error = 1;
            } else {
                add_zombie(casilla, (Tipo_casilla)tipo_zombie, config);
                casilla->zombies[casilla->cant_zombies - 1]->vida = vida_zombie;
            }
        }
    }
    // Si la lectura se corto por algo que no es el final del archivo, esta danado
    if (leidos != EOF && leidos != 6) {
        error = 1;
    }
    fclose(file);

    if (error) {
        clear_map(mapa);
        return NULL;
    }

    // Todo salio bien, recien ahora actualizamos las variables del juego
    *turno = t;
    *oleada_actual = o;
    *zombies_generados_oleada = z;
    *soles = s;
    *salud_casa = h;
    return mapa;
}
