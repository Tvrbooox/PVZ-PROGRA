#include "utils_map.h"

Jardin* load_map(const char* file_route){ //reserva memoria y carga matriz
    FILE* file = fopen(file_route, "r");
    if(file == NULL){
        printf("No se pudo leer el archivo\n");
        return 0;
    }
    
    Jardin* mapa = (Jardin*)malloc(sizeof(Jardin));//se reserva memoria para el struct
    if(!mapa){
        fclose(file);
        return 0;
    }

    if (fscanf(file, "%d %d", &(*mapa).fila, &((*mapa).columna)) != 2) {//se toman las dimensiones del archivo y se guardan
        fclose(file);
        free(mapa);
        return NULL;
    }

    (*mapa).grilla = (int**)malloc((*mapa).fila * sizeof(int*)); //se reservan filas como int
    for(int i=0; i<(*mapa).fila; i++){
        (*mapa).grilla[i] = (int*)malloc((*mapa).columna * sizeof(int));//se reservan columnas como int
        for(int j=0; j<(*mapa).columna; j++){
            fscanf(file, "%d", &((*mapa).grilla[i][j]));//lee valores del archivo y guarda en matriz dinamica
        }
    }

    fclose(file);
    return mapa;
}

void print_map(const Jardin* mapa){ //imprime la matriz dinamica
    if(!mapa){
        printf("Hubo un fallo al acceder al mapa\n");
        return;
    }
    printf("Mapa de %d x %d: \n", (*mapa).fila, (*mapa).columna);
    for(int i=0; i<(*mapa).fila; i++){
        for(int j=0; j<(*mapa).columna; j++){
            printf(" %d ", (*mapa).grilla[i][j]);
        }
        printf("\n");
    }
    return;
}

void clear_map(Jardin* mapa){//libera memoria de matriz
    if(!mapa){
        printf("Error al limpiar el mapa\n");
    }

    for(int i=0; i<(*mapa).fila; i++){ //se liberan los elementos de la matriz
        free((*mapa).grilla[i]);
    }

    free((*mapa).grilla); //se libera el puntero al arreglo
    free(mapa); //se libera la estructura
    return;
}

void make_map(const char* file_route, int filas, int columnas){//crea mapa aleatorio
    FILE* file = fopen(file_route, "w");
    if(file == NULL){
        printf("Error al leer archivo en creacion de mapa");
        return;
    } else {
        printf("Mapa aleatorio creado \n");
    }

    fprintf(file, "%d %d\n", filas, columnas);//escribe las dimensiones dentro del archivo
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){//60% probabilidad de 0 en casilla, 40% de que sea numero entre [1,9]
            int prob = rand() % 100;
            int value = 0;

            if(prob <=60){
                value = 0;
            } else {
                value = (rand() % 9) + 1;
            }
            fprintf(file, " %d ", value);//escribe la matriz en el archivo
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return;
}
