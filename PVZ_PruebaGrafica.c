#include "raylib.h"
#include <stdio.h>

int main(){


    int Matriz[5][9]={{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0}};
    InitWindow(1366, 768, "PVZ");

    int Tamaño_Celdas=50,Plata=250;
    int Plantas[3]={1,2,3},Seleccionado=0;
    int SolesX[5]={0,0,0,0,0};
    int SolesY[5]={0,0,0,0,0};
    float PocisionY[5]={0,0,0,0,0};

    Color ColoresTablero[5]={LIME,GREEN,YELLOW,DARKGREEN,BROWN};

    Color ColorOpciones[3]={LIGHTGRAY,LIGHTGRAY,LIGHTGRAY};

    SetTargetFPS(60);

    while(WindowShouldClose()==0){

        //CONFIG BASICA
        Vector2 mouse = GetMousePosition();


        //OPCIONES -----------------------------------------------------------------------------


        //Girasoles
        //Ya que aun no tengo la funcion de cuando se genera uno por ahora solo dejo que se genere con la letra G

        int SolX,SolY;

        if (IsKeyPressed(KEY_G)){
            int i=0;

            while(SolesX[i]!=0 && i<5){
                i++;
            }

            SolesX[i]=GetRandomValue(100, (Tamaño_Celdas*9));
            SolesY[i]=GetRandomValue(205,400);

            printf("Puesto %d: Coord x=%d y=%d\n",i,SolesX[i],SolesY[i]);
        }

        
        for(int i=0;i<5;i++){
            if(SolesX[i]!=0){

                Rectangle Sol={SolesX[i], PocisionY[i], 50,50};

                if(CheckCollisionPointRec(mouse,Sol)){

                    if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                        SolesX[i]=0;
                    }
                }
            }
        }


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
        for (int i=0;i<9;i++){
            for(int j=0;j<5;j++){
                Rectangle Tablero={100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas};

                if(CheckCollisionPointRec(mouse,Tablero)){

                    if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                        if(Matriz[j][i]==0){
                            Matriz[j][i]=Seleccionado;
                            Seleccionado=0;
                        }
                    }
                }


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

            printf("\n\n");
        }





        //GRAFICO ------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BROWN);


        DrawRectangle(45, 45, 170, 60, GRAY);
        for (int i=0;i<3;i++){
            DrawRectangle(50 + 55*i, 50, Tamaño_Celdas, Tamaño_Celdas, ColorOpciones[i]);
        }


        //IMPRIMIR LA MATRIZ EN PANTALLA
        for (int i=0;i<9;i++){
            for(int j=0;j<5;j++){

                if(Matriz[j][i]==0){
                    if(i%2==0) DrawRectangle(100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[j%2]);

                    else DrawRectangle(100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[(j+1)%2]);

                } else if(Matriz[j][i]==1) DrawRectangle(100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[2]);
                else if(Matriz[j][i]==2) DrawRectangle(100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[3]);
                if(Matriz[j][i]==3) DrawRectangle(100 + Tamaño_Celdas*i, 205 + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[4]);
                
            }
        }

        //GIRASOLES
        for(int i=0;i<5;i++){
            if(SolesX[i]!=0){

                if(PocisionY[i]<SolesY[i]){
                    PocisionY[i]+=(50.0f*GetFrameTime());
                }
                DrawRectangleV((Vector2){SolesX[i], PocisionY[i]},(Vector2){50,50}, YELLOW);
            }
        }
        
        
        


        

        EndDrawing();
    }
    CloseWindow();

    return 0;

}