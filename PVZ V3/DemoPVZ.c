#include "Funciones_Graficas.h"
#include "raylib.h"
#include <stdio.h>
#include <time.h>
#include "header.h"
#include "logica.h"
#include "guardado.h"

const char* elegir_nivel(int Opcion_Nivel) {
    if (Opcion_Nivel == 1) {
        return "config_facil.txt";
    } else if (Opcion_Nivel == 3) {
        return "config_dificil.txt";
    } else if (Opcion_Nivel == 2 || Opcion_Nivel == 4 || Opcion_Nivel == 5) {
        return "config_normal.txt";
    }

    return "";
}

int main(){

    InitWindow(1366, 768, "PVZ");
    InitAudioDevice();
    SetTargetFPS(60);

    int Opcion_Nivel = 0;
    int Pantalla = 0;

    Opcion_Nivel=Menu();
    if (Opcion_Nivel == 0) {
        CloseAudioDevice();
        CloseWindow();
        return 0;
    }
    
   //Cantidad de filas y columnas
   int NumFilas=3,NumColumnas=3;

    Config config = {0};
    if (!load_config(elegir_nivel(Opcion_Nivel), &config)) {
        printf("No se pudo cargar el archivo\n");
        CloseAudioDevice();
        CloseWindow();
        return 1;
    }
    printf("Configuración cargada correctamente.\n");

    Jardin *mapa = load_map("mapa_ceros.txt", &config);
    if (!mapa) {
        printf("No se pudo cargar el mapa inicial\n");
        CloseAudioDevice();
        CloseWindow();
        return 1;
    }
    printf("Mapa cargado con éxito (%d x %d).\n", mapa->fila, mapa->columna);

    Texture2D PersonalizadoMenu = LoadTexture("Personalizado.png");
    //personalizado
    while(Opcion_Nivel==4 && WindowShouldClose()==0){
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureEx(PersonalizadoMenu,(Vector2){-130,-150},0.0f ,1, WHITE);

        Rectangle MasFilas={375+65,385+40,80,80};
        Rectangle MenosFilas={510+65,385+40,80,80};
        Rectangle MasColumnas={682+65,385+40,80,80};
        Rectangle MenosColumnas={815+65,385+40,80,80};
        Rectangle Jugar={325+65,530+40,595,50};

        /*DrawRectangle(375+65,385+40,80,80,RED);

        DrawRectangle(510+65,385+40,80,80,RED);
        DrawRectangle(682+65,385+40,80,80,RED);
        DrawRectangle(815+65,385+40,80,80,RED);

        DrawRectangle(325+65,530+40,595,50,RED);*/

        if (CheckCollisionPointRec(mouse,MasFilas)){

            if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && NumFilas<10)){
                NumFilas++;
            }
        }else if (CheckCollisionPointRec(mouse,MenosFilas) && NumFilas>3){

            if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                NumFilas--;
            }
        }else if (CheckCollisionPointRec(mouse,MasColumnas) && NumColumnas<10){

            if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                NumColumnas++;
            }
        }else if (CheckCollisionPointRec(mouse,MenosColumnas) && NumColumnas>3){

            if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                NumColumnas--;
            }
        }else if (CheckCollisionPointRec(mouse,Jugar)){

            if((IsMouseButtonPressed(MOUSE_BUTTON_LEFT))){
                clear_map(mapa);
                mapa = create_custom_map(NumFilas, NumColumnas);
                if (!mapa) return 1;
                Opcion_Nivel=7;
            }
        }

        DrawText(TextFormat("%d",NumFilas), 540,350, 45, LIME);
        DrawText(TextFormat("%d",NumColumnas), 842,350, 45, LIME);

        EndDrawing();
    }

    //Configuraciones basicas
    if(Opcion_Nivel==5){ //Cargar
        NumFilas = mapa->fila;
        NumColumnas = mapa->columna;
    } 

    if(Opcion_Nivel<=3 && Opcion_Nivel>0){
        NumFilas=5;
        NumColumnas=9;
    }

/*____________________________________________
     ████ ████  ████  ███ █████ █████  ████ 
    █     █   █ █   █  █    █   █     █     
     ███  ████  ████   █    █   ████   ███  
        █ █     █  █   █    █   █         █ 
    ████  █     █   █ ███   █   █████ ████  
___________________________________________*/
    Texture2D fondo =LoadTexture("Fondo.png");
    Texture2D GirasolSprite =LoadTexture("GirasolSprite.png");
    Texture2D LanzaguisanteSprite =LoadTexture("LanzaguisanteSprite.png");
    Texture2D NuezSprite =LoadTexture("NuezSprite.png");
    Texture2D JalapenoSprite = LoadTexture("JalapenoSprite.png");
    Texture2D PatataSprite[2] = {LoadTexture("PatataBoomSprite2.png"),LoadTexture("PatataBoomDesactivadaSprite2.png")};
    Texture2D FuegoJalapenoSprite = LoadTexture("FuegoSprite.png");
    Texture2D SolSprite = LoadTexture("SolSprite.png");
    Texture2D ZombieSprite = LoadTexture("ZombieBaseSprite.png");
    Texture2D FlagZombieSprite = LoadTexture("FlagZombieSprite.png");
    Texture2D Pasto[2]={LoadTexture("Pasto_Claro.PNG"),LoadTexture("Pasto_Oscuro.PNG")};
    Texture2D Compra[7]={LoadTexture("GirasolCompra.png"),LoadTexture("LanzaguisantesCompra.png"),LoadTexture("NuezCompra.png"),LoadTexture("JalapenoCompra.png"),LoadTexture("PatataCompra.png"),LoadTexture("LanzaguisantesMejoraCompra.png"),LoadTexture("GirasolMejoraCompra.png")};
    Texture2D SeleccionSprite=LoadTexture("Seleccion.png");
    Texture2D GuisanteSprite=LoadTexture("GuisanteSprite.png");
    Texture2D ExplosionSprite=LoadTexture("Pow.png");
    Texture2D ContadorSoles=LoadTexture("ContadorSolesSprite.png");
    Texture2D PantallaDerrota=LoadTexture("PantallaDerrota.png");
    Texture2D LanzaguisantesMejoraSprite = LoadTexture("LanzaguisantesMejora.png");
    Texture2D GirasoLMejoraSprite = LoadTexture("GirasolDoble.png");
    Texture2D FootballZombie = LoadTexture("FootballZombie.png");
    Texture2D Ganaste = LoadTexture("Ganaste.png");
    Texture2D ContadorOleadas = LoadTexture("ContadorOleadas.PNG");

    Sound MordidaZombie = LoadSound("ZombieBite.ogg");
    Sound Plantar = LoadSound("plant.ogg");
    Sound SonidoSoles = LoadSound("points.ogg");
    Sound ExplosionJalapeno = LoadSound("jalapeno.ogg");
    Sound ExplosionPatata = LoadSound("potato_mine.ogg");
    Sound GuisanteSonido = LoadSound("shoop.ogg");
    Sound ImpactarGuisante = LoadSound("splat.ogg");


/*________________________________________________________
    █   █  ███  ████  ███  ███  ████  █     █████  ████ 
    █   █ █   █ █   █  █  █   █ █   █ █     █     █     
    █   █ █████ ████   █  █████ ████  █     ████   ███  
     █ █  █   █ █  █   █  █   █ █   █ █     █         █ 
      █   █   █ █   █ ███ █   █ ████  █████ █████ ████ 
_______________________________________________________*/ 

    //Configuracion matrices
    int MatrizNueva[NumFilas][NumColumnas];
    int MatrizGirasoles[NumFilas][NumColumnas];
    int MatrizLanzaguisantes[NumFilas][NumColumnas];    
    int MatrizNueces[NumFilas][NumColumnas];
    int MatrizJalapenos[NumFilas][NumColumnas];
    int MatrizPatatas[NumFilas][NumColumnas];


    Matriz_Ceros(NumFilas,NumColumnas,MatrizNueva);
    Matriz_Ceros(NumFilas,NumColumnas,MatrizLanzaguisantes);
    Matriz_Ceros(NumFilas,NumColumnas,MatrizNueces);
    Matriz_Ceros(NumFilas,NumColumnas,MatrizGirasoles);
    Matriz_Ceros(NumFilas,NumColumnas,MatrizJalapenos);
    Matriz_Ceros(NumFilas,NumColumnas,MatrizPatatas);

    //inicializar variables
    int soles = config.sol_inicial;
    int salud_casa = config.vida_casa;
    int turno = 0;
    int oleada_actual = 1;
    int zombies_generados_oleada = 0;

    //Variables de tiempo
    float TiempoAcomulado = 0.0f,TiempoActual=1.0f;




    //VARIABLES ENTIDADES

    //Variables para generar soles naturales
    float TiempoSoles=0;
    Sol Soles[10]={0};

    //Variables para generar soles en los soles
    Girasol Girasoles[10]={0};
    GirasolSol GirasolSoles[10]={0};

    //Variables para generar guisantes
    Guisante Guisantes[10]= {0};
    Lanzaguisante Lanzaguisantes[10]={0};

    //Variables para nueces
    Nuez Nueces[10]={0};

    //Variables para jalapeños
    Jalapeno Jalapenos[10]={0};
    FuegoJalapeno FuegoJalapenos[10]={0};

    //Variables para patatas
    Patata Patatas[10]={0};

    //Variables para zombies
    ZombieGrafico Zombies[20]={0};


    //VARIABLES APARIENCIA MATRIZ
    //Coordenada X e Y donde se inicia a dibujar la matriz en pantalla
    int CoordXInicio=305; 
    int CoordYInicio=130;

    //Tamaño en pixeles de las celdas segun el tamaño de la matriz
    int Tamaño_CeldasX=0;
    int Tamaño_CeldasY=0;
    Tamaño_CeldasX=(880/NumColumnas);
    Tamaño_CeldasY=(615/NumFilas);



    //VARIABLES MICELANEAS

    //Cantidad de soles
    int SolesActual=config.sol_inicial;

    //Variables para añadir plantas a la matriz
    int Seleccionado=0;

    int Precio[8]={0,50,100,50,25,125,150,250}; //Precio de cada planta en orden

    while(WindowShouldClose()==0 && Opcion_Nivel!=0){

        /*______________________________________________________________________
         ███   ███  █   █ █████ ███  ███  █   █ ████   ███   ███  ███  ███  █   █ 
        █     █   █ ██  █ █      █  █     █   █ █   █ █   █ █      █  █   █ ██  █ 
        █     █   █ █ █ █ ████   █  █  ██ █   █ ████  █████ █      █  █   █ █ █ █ 
        █     █   █ █  ██ █      █  █   █ █   █ █  █  █   █ █      █  █   █ █  ██ 
         ███   ███  █   █ █     ███  ███   ███  █   █ █   █  ███  ███  ███  █   █ 
        _________________________________________________________________________*/


        //CONFIGURACION RAYLIB
        Vector2 mouse = GetMousePosition();


        //CONFIGURACION PARTIDA
        //Añadir plantas a la matriz
        Seleccionado=ColisionesMatriz(CoordXInicio, CoordYInicio, Tamaño_CeldasX, Tamaño_CeldasY,NumFilas, NumColumnas, MatrizNueva,Seleccionado,mouse,&SolesActual,Precio,Plantar);

        //CONFIGURACION ENTIDADES

        //Funcion para configurar a los zombies conforme entran a la matriz dinamica
        ConfigurarZombie(mapa,Zombies,&config,ZombieSprite,FlagZombieSprite,FootballZombie,CoordYInicio,Tamaño_CeldasY);

        //Configurar parametros plantas
        ConfigurarPlantas(NumFilas,NumColumnas,MatrizNueva,MatrizNueces,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,Nueces,MatrizLanzaguisantes,Lanzaguisantes,MatrizGirasoles,Girasoles,MatrizJalapenos,Jalapenos,MatrizPatatas,Patatas,&config);

        //Configurar parametros plantas
        ConfigurarPlantas(NumFilas,NumColumnas,MatrizNueva,MatrizNueces,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,Nueces,MatrizLanzaguisantes,Lanzaguisantes,MatrizGirasoles,Girasoles,MatrizJalapenos,Jalapenos,MatrizPatatas,Patatas,&config);


        //TEMPORIZADORES

        //TEMPORIZADOR SOLES GENERADOS NATURALMENTE
        if(TiempoSoles>=24.0){
            TiempoSoles=0;
        } else TiempoSoles+=GetFrameTime();


        //TEMPORIZADORES PLANTAS
        for(int i=0;i<10;i++){

            //Cada cuanto debe atacar un lanzaguisantes normal

            if(Lanzaguisantes[i].activo){

                if(Lanzaguisantes[i].Mejora){
                    if(Lanzaguisantes[i].tiempo>=2.0){
                        Lanzaguisantes[i].tiempo=0;

                    } else Lanzaguisantes[i].tiempo+=GetFrameTime();
                }else {
                    if(Lanzaguisantes[i].tiempo>=1.5){
                        Lanzaguisantes[i].tiempo=0;

                    } else Lanzaguisantes[i].tiempo+=GetFrameTime();
                }
            }

            //Cuando debe de explotar el jalapeño
            if(Jalapenos[i].Activo && Jalapenos[i].Tiempo<1){
                Jalapenos[i].Tiempo+=GetFrameTime();
            }

            //Cuando las patatas estan activas para explotar
            if(Patatas[i].Activo && Patatas[i].Tiempo<15){
                Patatas[i].Tiempo+=GetFrameTime();
                Patatas[i].Sprite=PatataSprite[1];
                Patatas[i].ColisionExplosion=(Rectangle){CoordXInicio+Tamaño_CeldasX*(Patatas[i].Columna-1), CoordYInicio+ Tamaño_CeldasY*(Patatas[i].Fila-1),Tamaño_CeldasX*3,Tamaño_CeldasY*3};
            }
            if(Patatas[i].Activo && Patatas[i].Tiempo>=15){
                Patatas[i].Sprite=PatataSprite[0];
                Patatas[i].ExplosionActiva=true;
            }
        }

        //TEMPORIZADOR ATAQUE ZOMBIE
        for(int i=0;i<20;i++){

            if(Zombies[i].Activo && Zombies[i].TiempoGolpe<1){
                Zombies[i].TiempoGolpe+=GetFrameTime();
            } else Zombies[i].TiempoGolpe=0;
        }



        //BACKEND
        if(IsKeyPressed(KEY_ENTER)){
            printf("Se presiono enter");

            for(int i=0;i<20;i++){
                printf("Zombie[%d] esta activo: %d\n",i,Zombies[i].Activo);
            }

            printf("%d / %d\n",oleada_actual,config.max_oleadas);
        }

        if(IsKeyDown(KEY_UP) && IsKeyDown(KEY_DOWN) && IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_LEFT)){
            SolesActual+=1000000;
        }


        /*______________________________________________
        ███   ████   ███  █████ ███  ███   ███   ████ 
        █     █   █ █   █ █      █  █     █   █ █     
        █  ██ ████  █████ ████   █  █     █   █  ███  
        █   █ █  █  █   █ █      █  █     █   █     █ 
        ███   █   █ █   █ █     ███  ███   ███  ████ 
        ____________________________________________*/

        //CONFIGURACION PANTALLA
        BeginDrawing();
        ClearBackground(BLACK);

        //Añadir fondo
        DrawTexture(fondo, 0, -100, WHITE);

        //GRAFICOS JARDIN
        //Mapa sin plantas
        MostrarMatriz(CoordXInicio,CoordYInicio, NumFilas, NumColumnas,Tamaño_CeldasX,Tamaño_CeldasY,Pasto);
        //Mostrar las plantas
        MostrarPlanta(CoordXInicio, CoordYInicio, Tamaño_CeldasX, Tamaño_CeldasY, NumFilas, NumColumnas, MatrizNueva,GirasolSprite,LanzaguisanteSprite,NuezSprite,JalapenoSprite,Patatas,LanzaguisantesMejoraSprite,GirasoLMejoraSprite);

        //Seleccionar plantas del menu de compra
        ColisionTienda(mouse,&Seleccionado,Compra,SeleccionSprite);

        //SOLES
        //Contador de soles
        DrawTextureEx(ContadorSoles,(Vector2){825,35},0.0f ,0.55, WHITE);
        DrawText(TextFormat("%d",SolesActual), 890,45, 35, BLACK);

        //Soles generados naturalmente
        GenerarSol(Soles,mouse,TiempoSoles,&SolesActual,config.valor_sol,SolSprite,SonidoSoles);

        //Soles generados por girasol
        Generador_SolesGirasol(Girasoles,GirasolSoles,mouse,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio, CoordYInicio,&SolesActual,config.valor_sol,SolSprite,SonidoSoles);

        DrawTextureEx(ContadorOleadas,(Vector2){1000,20},0.0f ,0.15, WHITE);
        DrawText(TextFormat("%d / %d",oleada_actual, (config.max_oleadas+1)), 1045,58, 35, RED);

        //Zombies
        for(int i=0;i<20;i++){
            if(Zombies[i].Activo){
                if(Zombies[i].Tipo==6){
                    DrawTextureEx(Zombies[i].ColorZombie,(Vector2){Zombies[i].PosicionX-20,CoordYInicio-30+Tamaño_CeldasY*Zombies[i].Fila},0.0f ,0.09, WHITE);


                } else if(Zombies[i].Tipo==7){
                    DrawTextureEx(Zombies[i].ColorZombie,(Vector2){Zombies[i].PosicionX-35,CoordYInicio-40+Tamaño_CeldasY*Zombies[i].Fila},0.0f ,0.16, WHITE);
                }else if(Zombies[i].Tipo==8){
                    DrawTextureEx(Zombies[i].ColorZombie,(Vector2){Zombies[i].PosicionX-35,CoordYInicio-40+Tamaño_CeldasY*Zombies[i].Fila},0.0f ,0.12, WHITE);
                }

                if(Zombies[i].Detenerse!=true && Zombies[i].Velocidad>0) Zombies[i].PosicionX-=(Zombies[i].Velocidad*6)*GetFrameTime();

                Zombies[i].Colision=(Rectangle){Zombies[i].PosicionX,CoordYInicio+(Tamaño_CeldasY/2)+ Tamaño_CeldasY*Zombies[i].Fila, 40,40};
            }
        }


        //COLISIONES ENTIDADES-ZOMBIES

        //Guisantes lanzados por Lanzaguisantes
        Lanzar_Guisantes(NumFilas, NumColumnas,Tamaño_CeldasX,Tamaño_CeldasY,MatrizLanzaguisantes,Lanzaguisantes,Guisantes,Zombies,GuisanteSprite,GuisanteSonido);

        //Colisiones guisante
        ColisionesGuisante(Zombies,Guisantes,&config,ImpactarGuisante);

        //Colisiones Jalapeños
        ColisionesJalapenos(Jalapenos,FuegoJalapenos,NumFilas,NumColumnas,MatrizNueva,MatrizJalapenos,ExplosionJalapeno);

        //Dibujar fuego de los jalapenos
        DibujarFuegoJalapeno(FuegoJalapenos,CoordXInicio,CoordYInicio,Tamaño_CeldasX,Tamaño_CeldasY,FuegoJalapenoSprite,NumColumnas);

        //Colision
        ColisionFuegoJalapenos(Zombies,FuegoJalapenos);

        //Colision de las patatas
        ColisionPatata(Patatas,Zombies,ExplosionSprite,CoordXInicio,CoordYInicio,Tamaño_CeldasX,Tamaño_CeldasY,ExplosionPatata);

        for(int i=0;i<20;i++){
            //DrawRectangle(0,CoordYInicio,200,Tamaño_CeldasY*NumFilas-60,RED);
            Rectangle Casa={0,CoordYInicio,200,Tamaño_CeldasY*NumFilas-60};

            if(Zombies[i].Activo && (CheckCollisionRecs(Casa,Zombies[i].Colision))){
                Pantalla=1;
                Opcion_Nivel=0;
            }
        }


        //Colision Zombie - Lanzaguisante - Girasol - Nuez
        for(int i=0;i<10;i++){
            ColisionPlantaZombie(&Lanzaguisantes[i].activo,&Lanzaguisantes[i].Colision,&Lanzaguisantes[i].Vida, &Lanzaguisantes[i].CeldaX, &Lanzaguisantes[i].CeldaY, NumFilas, NumColumnas, MatrizNueva,MatrizLanzaguisantes,Zombies,i,2,MordidaZombie);
            ColisionPlantaZombie(&Nueces[i].Activo,&Nueces[i].Colision,&Nueces[i].Vida, &Nueces[i].Columna, &Nueces[i].Fila, NumFilas, NumColumnas, MatrizNueva,MatrizNueces,Zombies,i,3,MordidaZombie);
            ColisionPlantaZombie(&Girasoles[i].activo,&Girasoles[i].Colision,&Girasoles[i].Vida, &Girasoles[i].CoordX, &Girasoles[i].CoordY, NumFilas, NumColumnas, MatrizNueva,MatrizGirasoles,Zombies,i,1,MordidaZombie);
            ColisionPlantaZombie(&Jalapenos[i].Activo,&Jalapenos[i].Colision,&Jalapenos[i].Vida, &Jalapenos[i].Columna, &Jalapenos[i].Fila, NumFilas, NumColumnas, MatrizNueva,MatrizJalapenos,Zombies,i,4,MordidaZombie);
            ColisionPlantaZombie(&Patatas[i].Activo,&Patatas[i].Colision,&Patatas[i].Vida, &Patatas[i].Columna, &Patatas[i].Fila, NumFilas, NumColumnas, MatrizNueva,MatrizPatatas,Zombies,i,5,MordidaZombie);
        }

        //En caso que un zombie baje su vida abajo o igual que 0 esta funcion reincia sus parametros
        ZombieMuerto(Zombies);

        for (int i = 0; i < 20; i++) {
            if (Zombies[i].Activo && Zombies[i].Vida <= 0) {
                printf("ERROR: Zombie[%d] sigue activo con vida %d\n",
                    i, Zombies[i].Vida);
            }
        }

        if(oleada_actual==(config.max_oleadas)+1){
            int ZombiesVivos=0;
            for(int i=0;i<20;i++){
                if(Zombies[i].Activo){
                    ZombiesVivos++;
                }
            }
            if(ZombiesVivos==0){
                Pantalla=2;
                Opcion_Nivel=0;
            }
        }

        //PASAR DE RONDA
        //MAIN_2
        if(TiempoAcomulado>=TiempoActual){
            TiempoAcomulado-=TiempoActual;

            /*printf("\n======== ==================================");
            printf("\nTURNO: %d  |  OLEADA: %d/%d  |  SOLES: %d  |  SALUD CASA: %d\n", turno + 1, oleada_actual, config.max_oleadas, soles, salud_casa);
            printf("==========================================\n");*/

            avanzar_turno(mapa, &salud_casa, &soles, &config, &turno, &oleada_actual, &zombies_generados_oleada);
            //print_map(mapa);

        }
        TiempoAcomulado+=GetFrameTime();
        //TERMINA 

        EndDrawing();

    }

    while(Pantalla==1 && WindowShouldClose()==0){
        Vector2 mouse = GetMousePosition();

        //AQUI DEBO DE REINICIAR VARIABLES

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureEx(PantallaDerrota,(Vector2){70,-20},0.0f ,0.7, WHITE);
        //DrawRectangle(570,644,212,90,RED);
        Rectangle MenuBoton=(Rectangle){570,644,212,90};
        if (CheckCollisionPointRec(mouse,MenuBoton)){

            Opcion_Nivel=0;
            Pantalla=0;
        }

        EndDrawing();
    }

    while(Pantalla==2 && WindowShouldClose()==0){
        Vector2 mouse = GetMousePosition();

        //AQUI DEBO DE REINICIAR VARIABLES

        BeginDrawing();
        ClearBackground(BLACK);

        DrawTextureEx(Ganaste,(Vector2){70,-20},0.0f ,0.7, WHITE);
        //DrawTextureEx(PantallaDerrota,(Vector2){70,-20},0.0f ,0.7, WHITE);
        //DrawRectangle(570,644,212,90,RED);
        Rectangle MenuBoton=(Rectangle){570,644,212,90};
        if (CheckCollisionPointRec(mouse,MenuBoton)){

            Opcion_Nivel=0;
            Pantalla=0;
        }

        EndDrawing();
    }



    
}
