#include "Funciones_Graficas.h"
#include "raylib.h"
#include <stdio.h>

int main(){


    int Matriz[5][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
    int Matriz2[5][9]={{0,0,0,0,0,6,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,7,0,0,0,0,}};


    InitWindow(1366, 768, "PVZ");

    int Tamaño_Celdas=50,Plata=250;
    int Plantas[3]={1,2,3},Seleccionado=0;
    float PocisionY[5]={0,0,0,0,0};
    int CantidadZombies=0;
    float ZombiesX[5]={125+Tamaño_Celdas*8,125+Tamaño_Celdas*8,125+Tamaño_Celdas*8,125+Tamaño_Celdas*8,125+Tamaño_Celdas*8};
    float VelocidadRojo=Tamaño_Celdas/3,VelocidadAzul=Tamaño_Celdas/6;

    Color ColoresTablero[5]={LIME,GREEN,YELLOW,DARKGREEN,BROWN};

    Color ColorOpciones[3]={LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};

    int GSolX,GSolY;


    SetTargetFPS(60);


    
    //Variables para generar soles ---------------------------------
    int SolesMax=10;
    float TiempoSoles=0;

    int SolesX[SolesMax], SolesY[SolesMax];
    float PosicionY[SolesMax];

    for(int i=0;i<SolesMax;i++){
        SolesX[i]=0;
        SolesY[i]=0;
        PosicionY[i]=0;
    }

    //Variables para generar soles en girasoles -------------------------------------------
    int GirasolCoordX[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};
    int GirasolCoordY[10][10]={{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0}};


    int GirasolX[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int GirasolY[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    int GirasolConfirmar[5][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
    int AUX, CantidadGirasoles=-1;

    //Variables para generar guisantes
    int LanzaGuisanteX[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},LanzaGuisanteY[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
    float ProyectilPosicion[10]={0,0,0,0,0,0,0,0,0,0};
    int ZombieEnFila[10]={0,0,0,0,0};
    int MatrizConfirmacion[5][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};

    Guisante Guisantes[10]= {0};
    Lanzaguisante Lanzaguisantes[10]={0};


    
    
    while(WindowShouldClose()==0){

        

        //CONFIG BASICA
        Vector2 mouse = GetMousePosition();


        //OPCIONES -----------------------------------------------------------------------------

        //Seleccionar plantas

        for(int i=0; i<3;i++){
            Rectangle Opciones={50 + 55*i, 50, Tamaño_Celdas, Tamaño_Celdas};
            if (CheckCollisionPointRec(mouse,Opciones)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                    ColorOpciones[i]=GOLD;
                    Seleccionado=Plantas[i];
                } else{
                    ColorOpciones[i]=LIGHTGRAY;
                }
            }
        }


        //Añadir las plantas a la matriz

        Seleccionado=ColisionesMatriz(5, 9,Matriz, Tamaño_Celdas, 100, 205,Seleccionado,mouse);

        

        //Zombies
        CantidadZombies=0;
        for(int i=0;i<9;i++){
            for(int j=0;j<5;j++){
                if(Matriz2[j][i]!=0){
                    CantidadZombies++;
                }
            }
        }

        //Generador de soles de girasoles 
        for(int i=0;i<9;i++){
            for(int j=0;j<5;j++){

                if(Matriz[j][i]==1 && GirasolConfirmar[j][i]==0){

                    for(int k=0;k<10;k++){

                        if(GirasolX[k]==-1 && GirasolConfirmar[j][i]==0){

                            GirasolX[k]=i;
                            GirasolY[k]=j;
                            GirasolConfirmar[j][i]=1;

                        }
                    }
                    CantidadGirasoles++;
                }
            
            }
        }

        if(IsKeyPressed(KEY_H)){
            
            AUX=GetRandomValue(0,CantidadGirasoles);


            GSolX=GetRandomValue(80 + Tamaño_Celdas*GirasolX[AUX],140 + Tamaño_Celdas*GirasolX[AUX]);
            GSolY=GetRandomValue(195 + Tamaño_Celdas*GirasolY[AUX], 245 + Tamaño_Celdas*GirasolY[AUX]);

            /*GSolX=115 + Tamaño_Celdas*GirasolX[AUX];
            GSolY=220 + Tamaño_Celdas*GirasolY[AUX];*/

            for(int i=0;i<10;i++){
                if(GirasolCoordX[AUX][i]==0){
                    GirasolCoordX[AUX][i]=GSolX;
                    GirasolCoordY[AUX][i]=GSolY;
                    GSolX=0;
                    GSolY=0;
                }
            }
        } 


        
        //Guisantes de lanzaguisantes
        for(int i=0;i<9;i++){
            for(int j=0;j<5;j++){

                if(Matriz2[j][i]!=0){
                    ZombieEnFila[j]=1;
                }
            }
        }

        for(int i=0;i<10;i++){
            if(Lanzaguisantes[i].activo){

                if(Lanzaguisantes[i].tiempo>=1.5){
                    Lanzaguisantes[i].tiempo=0;
                } else Lanzaguisantes[i].tiempo+=GetFrameTime();
            }
        }
        

        //BACKEND ------------------------------------------------------------------------------
        //Imprimir la matriz en la terminal
        if(IsKeyPressed(KEY_ENTER)){
            for(int i=0;i<5;i++){
                for(int j=0;j<9;j++){
                    printf(" %d ",Matriz[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            for(int i=0;i<5;i++){
                for(int j=0;j<9;j++){
                    printf(" %d ",Matriz2[i][j]);
                }
                printf("\n");
            }
            printf("\n");
            printf("Cantidad de zombies: %d\n",CantidadZombies);

            for(int i=0;i<10;i++){
                printf("Girasol en x: %d, y: %d\n",LanzaGuisanteX[i],LanzaGuisanteY[i]);
            }

            for(int i=0;i<10;i++){
                printf("%d\n",Guisantes[i].activo);
            }

            printf("\n\n");
        }





        //GRAFICO ------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BROWN);

        

        //Mostrar opciones en pantalla
        DrawRectangle(45, 45, 170, 60, GRAY);
        for (int i=0;i<3;i++){
            DrawRectangle(50 + 55*i, 50, Tamaño_Celdas, Tamaño_Celdas, ColorOpciones[i]);
        }

        //IMPRIMIR LA MATRIZ EN PANTALLA

        MostrarMatriz(5, 9, Matriz, Tamaño_Celdas, 100, 205, ColoresTablero);

        //Mostrar plantas
        MostrarPlanta(5, 9, Matriz, Tamaño_Celdas);

        //Soles que caen en pantalla -----------------------------------------------
        if(TiempoSoles>=24.0){
            TiempoSoles=0;
        } else TiempoSoles+=GetFrameTime();
        
        
        Sol(SolesMax,Tamaño_Celdas,9,mouse,SolesX,SolesY,PosicionY,TiempoSoles);
        
        
        
    
        

        for(int i=0;i<CantidadZombies;i++){
            ZombiesX[i]-=VelocidadRojo*GetFrameTime();
        }

        //ZOMBIES EN PANTALLA
        for(int i=0;i<9;i++){
            for(int j=0;j<5;j++){
                if(Matriz2[j][i]!=0){
                    if(Matriz2[j][i]==6) {
                        DrawCircle(ZombiesX[0], 230 + Tamaño_Celdas*j, 20, RED);
                    }
                    else if(Matriz2[j][i]==7) DrawCircle(ZombiesX[0], 230 + Tamaño_Celdas*j, 20, BLUE);
                }
            }
        }


        //GIRASOL SOLES
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                Rectangle Solcito={GirasolCoordX[i][j], GirasolCoordY[i][j],25,25};

                if(GirasolCoordX[i][j]!=0){
                    
                    DrawRectangle(GirasolCoordX[i][j], GirasolCoordY[i][j],25,25, GOLD);
                    
                }

                if(CheckCollisionPointRec(mouse,Solcito)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT)) && GirasolCoordX[i][j]!=0){
                    GirasolCoordX[i][j]=0;
                    GirasolCoordY[i][j]=0;
                }
            }
            }
        }

        //GUISANTES LANZAGUISANTES

        Lanzar_Guisantes(Matriz,Tamaño_Celdas, ZombieEnFila,MatrizConfirmacion,Lanzaguisantes,Guisantes);

        
        
        
        EndDrawing();
    }
    CloseWindow();

    return 0;

}