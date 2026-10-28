#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils_config.h"

int main() {
    srand((unsigned int)time(NULL));
    Config mi_config = {0}; //load_config no usa mem. dinamica: importante inicializar en 0

    if (load_config("config.txt", &mi_config)) {//load_config y print_config toman la dir de memoria de la configuracion
        printf("Configuracion leida \n");
        // 3. Imprimir todos los valores cargados
        print_config(&mi_config);
    } else {
        printf("Error al cargar config \n");
    }

    return 0;
}