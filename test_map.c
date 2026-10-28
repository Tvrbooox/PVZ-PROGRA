#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils_map.h"

int main(){
    srand((unsigned int)time(NULL)); //importante para make_map
    make_map("mapa_0.txt", 5, 9);
    Jardin* mi_mapa = load_map("mapa_0.txt");//solo funciona si se crea mapa antes o se tiene mapa_0.txt en directorio
    if(mi_mapa){
        printf("Mapa cargado\n");
        print_map(mi_mapa);
        clear_map(mi_mapa);
    } else {
        printf("error al cargar el archivo\n");
    }

    return 0;
}