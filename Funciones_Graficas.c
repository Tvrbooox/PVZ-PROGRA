#include "Funciones_Graficas.h"
#include "raylib.h"
#include <stdio.h>



void MostrarMatriz(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas, int CoordenadaX, int CoordenadaY, Color *ColoresTablero){
    for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){

            if(i%2==0) DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[j%2]);

            else DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[(j+1)%2]);

            /*if(Matriz[j][i]==0){
                if(i%2==0) DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[j%2]);

                else DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[(j+1)%2]);

            } 
            else if(Matriz[j][i]==1) DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[2]);
            else if(Matriz[j][i]==2) DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[3]);
            else if(Matriz[j][i]==3) DrawRectangle(CoordenadaX + Tamaño_Celdas*i, CoordenadaY + Tamaño_Celdas*j, Tamaño_Celdas, Tamaño_Celdas, ColoresTablero[4]);*/
                
        }
    }
}

int ColisionesMatriz(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas,int CoordenadaX, int CoordenadaY,int Seleccionado,Vector2 mouse){

    for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){
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
    return Seleccionado;
}

void Sol(int SolesMax,int Tamaño_Celdas,int CantidadCeldasX,Vector2 mouse,int SolesX[SolesMax], int SolesY[SolesMax], float PosicionY[SolesMax],float Tiempo){
    int SolX=0,SolY=0;

    if(Tiempo>=24.0){
        SolX=GetRandomValue(100, (Tamaño_Celdas*9));
        SolY=GetRandomValue(205,400);
        printf("Sol generado en x: %d, y: %d\n",SolX,SolY);

        for(int i=0;i<SolesMax;i++){
            if(SolesX[i]==0){
                SolesX[i]=SolX;
                SolesY[i]=SolY;
                SolX=0;
                SolY=0;
            }
        }
    }

    for(int i=0;i<SolesMax;i++){
        if(SolesX[i]!=0){

            //COLISION ------------------------
            Rectangle Sol={SolesX[i],PosicionY[i],50,50};

            //DIBUJAR EN PANTALLA ------------------------------------
            if(PosicionY[i]<SolesY[i]){
                PosicionY[i]+=(50.0f*GetFrameTime());
            }
            DrawRectangleV((Vector2){SolesX[i], PosicionY[i]},(Vector2){50,50}, YELLOW);

            if(CheckCollisionPointRec(mouse,Sol)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                    SolesX[i]=0;
                    SolesY[i]=0;
                    PosicionY[i]=0.f;
                }
            }
        }
    }

}

void MostrarPlanta(int Alto, int Ancho, int Matriz[Alto][Ancho], int Tamaño_Celdas){
    for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){

            if(Matriz[j][i]==1) DrawCircle(125 + Tamaño_Celdas*i, 230 + Tamaño_Celdas*j, 20, YELLOW);
            else if(Matriz[j][i]==2) DrawCircle(125 + Tamaño_Celdas*i, 230 + Tamaño_Celdas*j, 20, DARKGREEN);
            else if(Matriz[j][i]==3) DrawCircle(125 + Tamaño_Celdas*i, 230 + Tamaño_Celdas*j, 20, BROWN);
                
        }
    }
}


void Lanzar_Guisantes(int Matriz[5][9],int Tamaño_Celdas, int ZombieEnFila[5],int MatrizConfirmacion[5][9],Lanzaguisante Lanzaguisantes[10],Guisante Guisantes[10]){


    for(int i=0;i<5;i++){


        if(ZombieEnFila[i]!=0){


            for(int j=0;j<9;j++){

                if(Matriz[i][j]==2 && MatrizConfirmacion[i][j]==0){
                    for(int k=0;k<10;k++){

                        if(!Lanzaguisantes[k].activo){

                            Lanzaguisantes[k].activo=true;
                            MatrizConfirmacion[i][j]=1;
                            Lanzaguisantes[k].CeldaX=j;
                            Lanzaguisantes[k].CeldaY=i;
                            break;
                        }
                    }
                }
            }
        }
    }

    for(int i=0;i<5;i++){


        if(ZombieEnFila[i]!=0){

            for(int j=0;j<9;j++){


                for(int l=0;l<10;l++){

                    if(Lanzaguisantes[l].CeldaY==i){

                        if(Matriz[i][j]==2 && Lanzaguisantes[l].tiempo>=1.5){
                            for(int k=0;k<10;k++){

                                if(Guisantes[k].activo==0){

                                    Guisantes[k].posicion=(Vector2){125 + Tamaño_Celdas*j, 230 + Tamaño_Celdas*i};
                                    Guisantes[k].posicionInicial=(Vector2){125 + Tamaño_Celdas*j, 230 + Tamaño_Celdas*i};
                                    Guisantes[k].activo=true;
                                    MatrizConfirmacion[i][j]=1;
                                    //MatrizConfirmacion[i][j]=1;
                                    break;
                                }
                            }
                        }
                    }
                }
                
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

    for(int i=0;i<10;i++){
        if(Guisantes[i].activo){
            Guisantes[i].posicion.x+=80.0f*GetFrameTime();
            DrawCircleV(Guisantes[i].posicion,15, DARKGREEN);
        }
    }
}