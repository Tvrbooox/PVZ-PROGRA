#include "Funciones_Graficas.h"
#include "raylib.h"
#include <stdio.h>



void MostrarMatriz(int CoordXInicio, int CoordYInicio, int NumFilas, int NumColumnas, int Tamaño_CeldasX,int Tamaño_CeldasY,Texture2D Pasto[2]){

    Rectangle Recorte={0.0f, 0.0f,(float)Tamaño_CeldasX,(float)Tamaño_CeldasY};

    for(int i=0;i<NumColumnas;i++){

        for(int j=0;j<NumFilas;j++){

            
            if(i%2==0) DrawTextureRec(Pasto[j%2], Recorte,(Vector2){CoordXInicio +Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j}, WHITE);
            //DrawRectangle(CoordXInicio +Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j, Tamaño_CeldasX, Tamaño_CeldasY, ColoresTablero[j%2]);
            else DrawTextureRec(Pasto[(j+1)%2], Recorte,(Vector2){CoordXInicio +Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j}, WHITE);
            //DrawRectangle(CoordXInicio + Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j, Tamaño_CeldasX, Tamaño_CeldasY, ColoresTablero[(j+1)%2]);
            
        }
    }
}

int ColisionesMatriz(int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY,int Alto, int Ancho, int Matriz[Alto][Ancho],int Seleccionado,Vector2 mouse,int *SolesActuales,int Valor[6],Sound plant){

    for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){
            Rectangle Tablero={CoordXInicio + Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j, Tamaño_CeldasX, Tamaño_CeldasY};

            if(CheckCollisionPointRec(mouse,Tablero)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                    if(Matriz[j][i]==0 && *SolesActuales>=Valor[Seleccionado] && Seleccionado>0 && Seleccionado<=5){
                        Matriz[j][i]=Seleccionado;
                        *SolesActuales-=Valor[Seleccionado];
                        Seleccionado=0;
                        PlaySound(plant);
                        
                    } else if (Matriz[j][i]==2 && *SolesActuales>=Valor[Seleccionado] && Seleccionado==6){
                        Matriz[j][i]=Seleccionado;
                        *SolesActuales-=Valor[Seleccionado];
                        Seleccionado=0;
                        PlaySound(plant);
                    } else if(Matriz[j][i]==1 && *SolesActuales>=Valor[Seleccionado] && Seleccionado==7){
                        Matriz[j][i]=Seleccionado;
                        *SolesActuales-=Valor[Seleccionado];
                        Seleccionado=0;
                        PlaySound(plant);
                    } else Seleccionado=0;
                }
            }


        }
    }
    return Seleccionado;
}

void GenerarSol(int MaxEntidades,Sol Soles[MaxEntidades], Vector2 mouse,float TiempoSoles, int *SolesActuales,int ValorSol,Texture2D SolSprite,Sound Sonido){
    if(TiempoSoles>=24.0){

        for(int i=0;i<MaxEntidades;i++){
            if(Soles[i].activo==false){
                Soles[i].FinalX=GetRandomValue(305, 1185);
                Soles[i].FinalY=GetRandomValue(130,745);
                Soles[i].activo=true;
                break;
            }
        }
    }

    for(int i=0;i<MaxEntidades;i++){

        if(Soles[i].activo){
            //Rectangle SolColision={Soles[i].FinalX,Soles[i].Posicion,50,50};
            Rectangle SolColision={Soles[i].FinalX, Soles[i].Posicion,70,70};
            DrawTextureEx(SolSprite,(Vector2){Soles[i].FinalX,Soles[i].Posicion},0.0f ,0.4, WHITE);

            if(Soles[i].Posicion<Soles[i].FinalY){
                Soles[i].Posicion+=(50.0f*GetFrameTime());
            }

            if(CheckCollisionPointRec(mouse,SolColision)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                    Soles[i].FinalX=0;
                    Soles[i].FinalY=0;
                    Soles[i].Posicion=0.f;
                    Soles[i].activo=false;
                    *SolesActuales+=ValorSol;
                    PlaySound(Sonido);
                }
            }
        }
    }
}


void MostrarPlanta(int MaxEntidades,int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY, int Alto, int Ancho, int Matriz[Alto][Ancho],Texture2D GirasolSprite,Texture2D LanzaguisanteSprite,Texture2D NuezSprite,Texture2D JalapenoSprite, Patata Patatas[MaxEntidades],Texture2D LanzaguisanteMejoraSprite, Texture2D GirasolMejoraSprite){
    /*int Radio;
    if(Tamaño_CeldasX<Tamaño_CeldasY){
        Radio=(Tamaño_CeldasX/2)-15;
    } else{
        Radio=(Tamaño_CeldasY/2)-15;
    }*/

    /*for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){

            if(Matriz[j][i]==1){
                DrawTextureEx(GirasolSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.09, WHITE);
                //DrawTexture(GirasolSprite, CoordXInicio +Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j, WHITE);
            } //DrawCircle(CoordXInicio+(Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio,YELLOW);
            else if(Matriz[j][i]==2) {
                DrawTextureEx(LanzaguisanteSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.2, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, DARKGREEN);
            } else if(Matriz[j][i]==3){
                DrawTextureEx(NuezSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.18, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }else if(Matriz[j][i]==4){
                DrawTextureEx(JalapenoSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.14, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }else if(Matriz[j][i]==5){

                DrawTextureEx(PatataSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.2, WHITE);

                if(k==0){
                    DrawTextureEx(PatataSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.16, WHITE);
                    //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
                } else DrawTextureEx(PatataSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.16, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }
        }
    }*/

    for (int i=0;i<Ancho;i++){
        for(int j=0;j<Alto;j++){
            if(Matriz[j][i]==1){
                DrawTextureEx(GirasolSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.09, WHITE);
                //DrawTexture(GirasolSprite, CoordXInicio +Tamaño_CeldasX*i, CoordYInicio + Tamaño_CeldasY*j, WHITE);
            } //DrawCircle(CoordXInicio+(Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio,YELLOW);
            else if(Matriz[j][i]==2) {
                DrawTextureEx(LanzaguisanteSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.2, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, DARKGREEN);
            } else if(Matriz[j][i]==3){
                DrawTextureEx(NuezSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.18, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }else if(Matriz[j][i]==4){
                DrawTextureEx(JalapenoSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.14, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }else if(Matriz[j][i]==5){

                for(int k=0;k<MaxEntidades;k++){
                    if(Patatas[k].Activo && Patatas[k].Fila==j && Patatas[k].Columna==i){
                        DrawTextureEx(Patatas[k].Sprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.2, WHITE);
                    }
                }
            }else if(Matriz[j][i]==6){
                DrawTextureEx(LanzaguisanteMejoraSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.24, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }else if(Matriz[j][i]==7){
                DrawTextureEx(GirasolMejoraSprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*i, CoordYInicio+5+ Tamaño_CeldasY*j},0.0f ,0.18, WHITE);
                //DrawCircle(CoordXInicio + (Tamaño_CeldasX/2) +Tamaño_CeldasX*i, CoordYInicio + (Tamaño_CeldasY/2) + Tamaño_CeldasY*j, Radio, BROWN);
            }
        }
    }




}

//void Lanzar_Guisantes(int NumFilas, int NumColumnas, int Matriz[NumFilas][NumColumnas],int Tamaño_CeldasX,int Tamaño_CeldasY, int ZombieEnFila[NumFilas],int MatrizConfirmacion[NumFilas][NumColumnas],Lanzaguisante Lanzaguisantes[10],Guisante Guisantes[10],int VidaLanzaguisantes){
void Lanzar_Guisantes(int MaxEntidades,int NumFilas, int NumColumnas,int Tamaño_CeldasX,int Tamaño_CeldasY,int MatrizConfirmacion[NumFilas][NumColumnas],Lanzaguisante Lanzaguisantes[10],Guisante Guisantes[10],ZombieGrafico Zombies[20],Texture2D Guisante,Sound Sonido){

    for(int i=0;i<MaxEntidades;i++){
        Rectangle Colision={305+Tamaño_CeldasX*Lanzaguisantes[i].CeldaX,130+Tamaño_CeldasY*Lanzaguisantes[i].CeldaY,Tamaño_CeldasY*NumFilas,Tamaño_CeldasX};
        for(int j=0;j<20;j++){

            if(CheckCollisionRecs(Colision,Zombies[j].Colision) && Lanzaguisantes[i].activo && Zombies[j].Activo && Lanzaguisantes[i].tiempo>=1.5 && Lanzaguisantes[i].tiempo<1.55){

                for(int k=0;k<MaxEntidades;k++){

                    if(Guisantes[k].activo==0){

                        Guisantes[k].posicion=(Vector2){305 + (Tamaño_CeldasX/2) + Tamaño_CeldasX*Lanzaguisantes[i].CeldaX, 130 + (Tamaño_CeldasY/2)+ Tamaño_CeldasY*Lanzaguisantes[i].CeldaY};
                        Guisantes[k].posicionInicial=(Vector2){305 + (Tamaño_CeldasX/2)+ Tamaño_CeldasX*j, 130 + (Tamaño_CeldasY/2) + Tamaño_CeldasY*i};
                        Guisantes[k].activo=true;
                        MatrizConfirmacion[i][j]=1;
                        PlaySound(Sonido);
                        break;
                    }
                }
            }

            if(CheckCollisionRecs(Colision,Zombies[j].Colision) && Lanzaguisantes[i].activo && Zombies[j].Activo && Lanzaguisantes[i].tiempo>=1.55 && Lanzaguisantes[i].tiempo<1.6 && Lanzaguisantes[i].Mejora){

                for(int k=0;k<MaxEntidades;k++){

                    if(Guisantes[k].activo==0){

                        Guisantes[k].posicion=(Vector2){305 + (Tamaño_CeldasX/2) + Tamaño_CeldasX*Lanzaguisantes[i].CeldaX, 130 + (Tamaño_CeldasY/2)+ Tamaño_CeldasY*Lanzaguisantes[i].CeldaY};
                        Guisantes[k].posicionInicial=(Vector2){305 + (Tamaño_CeldasX/2)+ Tamaño_CeldasX*j, 130 + (Tamaño_CeldasY/2) + Tamaño_CeldasY*i};
                        Guisantes[k].activo=true;
                        MatrizConfirmacion[i][j]=1;
                        PlaySound(Sonido);
                        break;
                    }
                }
            }

        }
    }

    for(int i=0;i<MaxEntidades;i++){
        if(Lanzaguisantes[i].activo){

            if(Lanzaguisantes[i].tiempo>=1.5){
                Lanzaguisantes[i].tiempo=0;
            } else Lanzaguisantes[i].tiempo+=GetFrameTime();
        }
    }

    for(int i=0;i<MaxEntidades;i++){
        if(Guisantes[i].activo){
            Guisantes[i].posicion.x+=220.0f*GetFrameTime();
            DrawTextureEx(Guisante,(Vector2){Guisantes[i].posicion.x-12,Guisantes[i].posicion.y-12},0.0f ,1.2, WHITE);
            //DrawCircleV((Vector2){Guisantes[i].posicion.x,Guisantes[i].posicion.y},15, DARKGREEN);

            Guisantes[i].Colision=(Rectangle){Guisantes[i].posicion.x,Guisantes[i].posicion.y,15,15};
        }
    }


}

void Generador_SolesGirasol(int MaxEntidades,Girasol Girasoles[MaxEntidades],GirasolSol GirasolSoles[MaxEntidades], Vector2 mouse,int Tamaño_CeldasX,int Tamaño_CeldasY,int CoordXInicio, int CoordYInicio, int *SolesActuales, int ValorSol,Texture2D SolSprite,Sound Sonido){

    for(int i=0;i<MaxEntidades;i++){

        if(Girasoles[i].activo){
            if(Girasoles[i].tiempo<25.0){
                Girasoles[i].tiempo+=GetFrameTime();
            } else Girasoles[i].tiempo=0;
            
        } 
    }

    for(int j=0;j<MaxEntidades;j++){

        if(Girasoles[j].tiempo>=25.0){
            int k=1;
            if(Girasoles[j].Mejora){
                k=2;
            }
            for(int m=0;m<k;m++){
                for(int i=0;i<MaxEntidades;i++){

                    if(GirasolSoles[i].activo==false){
                        GirasolSoles[i].activo=true;
                        GirasolSoles[i].CoordX=GetRandomValue(CoordXInicio-(Tamaño_CeldasX/2)+40+ Tamaño_CeldasX*Girasoles[j].CoordX,CoordXInicio+(Tamaño_CeldasX/2)+40 + Tamaño_CeldasX*Girasoles[j].CoordX);
                        GirasolSoles[i].CoordY=GetRandomValue(CoordYInicio-(Tamaño_CeldasY/2)+40+ Tamaño_CeldasY*Girasoles[j].CoordY,CoordYInicio+(Tamaño_CeldasY/2)+40 + Tamaño_CeldasY*Girasoles[j].CoordY);
                        break;
                    }
                }
            }
            
        }


    }

    for(int i=0;i<MaxEntidades;i++){
        if(GirasolSoles[i].activo){
            Rectangle Solcito={GirasolSoles[i].CoordX, GirasolSoles[i].CoordY,70,70};
                
            DrawTextureEx(SolSprite,(Vector2){GirasolSoles[i].CoordX,GirasolSoles[i].CoordY},0.0f ,0.4, WHITE);
            //DrawRectangle(GirasolSoles[i].CoordX, GirasolSoles[i].CoordY,70,70, GOLD);


            if(CheckCollisionPointRec(mouse,Solcito)){

                if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                    GirasolSoles[i].CoordX=0;
                    GirasolSoles[i].CoordY=0;
                    GirasolSoles[i].activo=false;
                    *SolesActuales+=ValorSol;
                    PlaySound(Sonido);
                }
            }
        }
    }

}

void ColisionPlantaZombie(bool *PlantaActivo, Rectangle *PlantaColision, int *PlantaVida, int *PlantaCoordX, int *PlantaCoordY, int NumFilas, int NumColumnas, int MatrizNueva[NumFilas][NumColumnas], int MatrizConfirmacion[NumFilas][NumColumnas], ZombieGrafico Zombies[20],int i, int Identificador,Sound Mordida){
    for(int j=0;j<20;j++){

        if(Zombies[j].Activo && *PlantaActivo){

            if(CheckCollisionRecs(*PlantaColision,Zombies[j].Colision) && *PlantaActivo && Zombies[j].Activo && Zombies[j].TiempoGolpe>=1.0){
                //PlantaVida[i]-=config.dmg_zombie_base;
                *PlantaVida-=Zombies[j].Daño;
                Zombies[j].Detenerse=1;
                Zombies[j].Interactuando=((Identificador*100)+i);
                PlaySound(Mordida);
                //printf("Planta[%d] | Zombie[%d] | Vida: %d\n",Identificador,j,*PlantaVida);
            }
        }

        if(*PlantaVida<=0 && *PlantaActivo){
            //printf("Vida Lanzaguisantes<=0\n");
            *PlantaActivo=false;
            *PlantaColision=(Rectangle){0,0,0,0};
            MatrizNueva[*PlantaCoordY][*PlantaCoordX]=0;
            MatrizConfirmacion[*PlantaCoordY][*PlantaCoordX]=0;

            for(int k=0;k<20;k++){
                if(Zombies[k].Activo && (Zombies[k].Interactuando-(Identificador*100))==i)
                Zombies[k].Detenerse=false;
                Zombies[k].Interactuando=0;
            }
        }
    }
    
}

int OrdenarParametros(int iFilas, int jColumnas, bool *PlantaActivo, int *PlantaVida, Rectangle *PlantaColision, int *PlantaCoordX, int *PlantaCoordY,int Ancho, int Alto,int Tamaño_CeldasX, int Tamaño_CeldasY, int CoordXInicio, int CoordYInicio,int Vida){

    if(*PlantaActivo==false){

        *PlantaActivo=true;
        *PlantaVida=Vida;
        *PlantaColision=(Rectangle){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*jColumnas, CoordYInicio+5+ Tamaño_CeldasY*iFilas,Ancho,Alto};
        *PlantaCoordY=iFilas;
        *PlantaCoordX=jColumnas;
        return 1;
    } else return 0;
}

void Matriz_Ceros(int NumFilas, int NumColumnas, int Matriz[NumFilas][NumColumnas]){
    for(int i=0;i<NumFilas;i++){

        for(int j=0;j<NumColumnas;j++){

            Matriz[i][j]=0;
        }
    }
}

void ConfigurarPlantas(int MaxEntidades,int NumFilas,int NumColumnas,int MatrizNueva[NumFilas][NumColumnas],int MatrizNueces[NumFilas][NumColumnas],int Tamaño_CeldasX,int Tamaño_CeldasY,int CoordXInicio,int CoordYInicio, Nuez Nueces[MaxEntidades],int MatrizLanzaguisantes[NumFilas][NumColumnas],Lanzaguisante Lanzaguisantes[MaxEntidades],int MatrizGirasoles[NumFilas][NumColumnas], Girasol Girasoles[MaxEntidades],int MatrizJalapenos[NumFilas][NumColumnas], Jalapeno Jalapenos[MaxEntidades],int MatrizPatatas[NumFilas][NumColumnas],Patata Patatas[MaxEntidades],Config *config){
    int Validar=0;

    for(int i=0;i<NumFilas;i++){
        for(int j=0;j<NumColumnas;j++){
            if(MatrizNueva[i][j]==3 && MatrizNueces[i][j]==0){
                MatrizNueces[i][j]=1;
                for(int k=0;k<MaxEntidades;k++){
                    Validar=OrdenarParametros(i,j,&Nueces[k].Activo, &Nueces[k].Vida, &Nueces[k].Colision, &Nueces[k].Columna, &Nueces[k].Fila,88,102,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,config->vida_nuez);
                    if(Validar==1) break;

                }
                Validar=0;


            } if(MatrizNueva[i][j]==2 && MatrizLanzaguisantes[i][j]==0){
                MatrizLanzaguisantes[i][j]=1;

                for(int k=0;k<MaxEntidades;k++){
                    Validar=OrdenarParametros(i,j,&Lanzaguisantes[k].activo, &Lanzaguisantes[k].Vida, &Lanzaguisantes[k].Colision, &Lanzaguisantes[k].CeldaX, &Lanzaguisantes[k].CeldaY,88,89,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,config->vida_lanzaguisante);
                    if(Validar==1) break;
                }
                Validar=0;

            } if(MatrizNueva[i][j]==1 && MatrizGirasoles[i][j]==0){
                MatrizGirasoles[i][j]=1;

                for(int k=0;k<MaxEntidades;k++){
                    Validar=OrdenarParametros(i,j,&Girasoles[k].activo, &Girasoles[k].Vida, &Girasoles[k].Colision, &Girasoles[k].CoordX, &Girasoles[k].CoordY,83,94,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,config->vida_girasol);
                    if(Validar==1) break;
                }
                Validar=0;

            } if(MatrizNueva[i][j]==4 && MatrizJalapenos[i][j]==0){
                MatrizJalapenos[i][j]=1;

                for(int k=0;k<MaxEntidades;k++){
                    Validar=OrdenarParametros(i,j,&Jalapenos[k].Activo, &Jalapenos[k].Vida, &Jalapenos[k].Colision, &Jalapenos[k].Columna, &Jalapenos[k].Fila,61,107,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,config->vida_patata); //NO HAY VIDA PARA JALAPEÑO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    if(Validar==1) break;
                } Validar=0;

            }  if(MatrizNueva[i][j]==5 && MatrizPatatas[i][j]==0){
                MatrizPatatas[i][j]=1;

                for(int k=0;k<MaxEntidades;k++){
                    Validar=OrdenarParametros(i,j,&Patatas[k].Activo, &Patatas[k].Vida, &Patatas[k].Colision, &Patatas[k].Columna, &Patatas[k].Fila,96,70,Tamaño_CeldasX,Tamaño_CeldasY,CoordXInicio,CoordYInicio,config->vida_patata);
                    if(Validar==1) break;
                } Validar=0;
            }if(MatrizNueva[i][j]==6 && MatrizLanzaguisantes[i][j]==1){
                MatrizLanzaguisantes[i][j]=2;

                for(int k=0;k<MaxEntidades;k++){
                    if(Lanzaguisantes[k].CeldaY==i && Lanzaguisantes[k].CeldaX==j){
                        Lanzaguisantes[k].Mejora=true;
                    }
                }
            }if(MatrizNueva[i][j]==7 && MatrizGirasoles[i][j]==1){
                MatrizGirasoles[i][j]=2;

                for(int k=0;k<MaxEntidades;k++){
                    if(Girasoles[k].CoordY==i && Girasoles[k].CoordX==j){
                        Girasoles[k].Mejora=true;
                    }
                }
            }
        }
    }
}

int Menu(Music TemaMenu){
    Texture2D MenuInicial=LoadTexture("MenuInicio.png");
    Texture2D MenuJugar=LoadTexture("MenuNiveles.png");

    int Pantalla=1;//Opcion=0;
    PlayMusicStream(TemaMenu);

    while(Pantalla==1 && WindowShouldClose()==0){
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(WHITE);
        UpdateMusicStream(TemaMenu);

        DrawTextureEx(MenuInicial,(Vector2){0,0},0.0f ,1.5, WHITE);
        /*DrawRectangle(750,90,380,100,RED);
        DrawRectangle(740,220,370,110,RED);
        DrawRectangle(750,360,330,110,RED);*/

        Rectangle Opcion_Jugar=(Rectangle){750,90,380,100};
        //Rectangle Opcion_Tutorial=(Rectangle){740,220,370,110};
        Rectangle Opcion_Salir=(Rectangle){750,360,330,110};

        if (CheckCollisionPointRec(mouse,Opcion_Jugar)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=2;
            }
        } /*else if (CheckCollisionPointRec(mouse,Opcion_Tutorial)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=3;
            }
        }*/ else if (CheckCollisionPointRec(mouse,Opcion_Salir)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=0;
                return 0;
            }
        }
        EndDrawing();

    }
    
    while(Pantalla==2 && WindowShouldClose()==0){
        Vector2 mouse = GetMousePosition();
        UpdateMusicStream(TemaMenu);

        BeginDrawing();
        ClearBackground(WHITE);

        DrawTextureEx(MenuJugar,(Vector2){0,0},0.0f ,1.4, WHITE);

        Rectangle Nivel_Cargar=(Rectangle){150,490,180,70};
        Rectangle Nivel_Personalizado=(Rectangle){360,515,220,60};
        Rectangle Nivel_Facil=(Rectangle){610,425,200,70};
        Rectangle Nivel_Medio=(Rectangle){890,490,160,80};
        Rectangle Nivel_Dificil=(Rectangle){1080,510,160,80};


        if (CheckCollisionPointRec(mouse,Nivel_Cargar)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=4;
                return 5;
            }
        } else if (CheckCollisionPointRec(mouse,Nivel_Personalizado)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=5;
                return 4;
            }
        } else if (CheckCollisionPointRec(mouse,Nivel_Facil)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=6;
                return 1;
            }
        } else if (CheckCollisionPointRec(mouse,Nivel_Medio)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=6;
                return 2;
            }
        } else if (CheckCollisionPointRec(mouse,Nivel_Dificil)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                Pantalla=6;
                return 3;
            }
        } 

        EndDrawing();

    }
    UnloadMusicStream(TemaMenu);

    return 0;

}

void ColisionTienda(Vector2 mouse,int *Seleccionado,Texture2D Compra[7],Texture2D SeleccionadoSprite){

    char PrecioTexto[7][4]={"50","100","50","25","125","150","250"};
    int Plantas[7]={1,2,3,4,5,6,7};


    for(int i=0; i<7;i++){
        Rectangle Opciones={30 + 110*i,25,109,70};
        if (CheckCollisionPointRec(mouse,Opciones)){

            if((IsMouseButtonDown(MOUSE_BUTTON_LEFT))){
                *Seleccionado=Plantas[i];
            }
        }

        DrawTextureEx(Compra[i],(Vector2){30 + 110*i,25},0.0f ,1, WHITE);
        DrawText(PrecioTexto[i], 100+110*i,65, 20, BLACK);

        if(*Seleccionado!=0){
            DrawTextureEx(SeleccionadoSprite,(Vector2){20 + 110*(*Seleccionado-1),25},0.0f ,1, WHITE);
        }
    }
}

void ConfigurarZombie(Jardin *mapa, ZombieGrafico Zombies[20],Config *config, Texture2D ZombieSprite, Texture2D FlagZombieSprite,Texture2D FootballZombie,int CoordYInicio,int Tamaño_CeldasY){

    for (int i = 0; i < mapa->fila; i++) {
        for (int j = 0; j < mapa->columna; j++) {

            Casilla *casilla = &mapa->grilla[i][j];
            if(casilla->cant_zombies>0){

                while (casilla->cant_zombies>0) {
                    Entidad *zombie = casilla->zombies[0];

                    for(int l=0;l<20;l++){
                        if(Zombies[l].Activo==false){
                            Zombies[l].Activo=true;
                            printf("ACTIVANDO Zombie[%d], tipo=%d, vida=%d\n",l, zombie->tipo, zombie->vida);
                            Zombies[l].Fila=i;
                            Zombies[l].Tipo=zombie->tipo;
                            Zombies[l].Vida=zombie->vida;
                            Zombies[l].PosicionX=1185;
                            Zombies[l].Detenerse=false;
                            Zombies[l].Colision=(Rectangle){1185,CoordYInicio+(Tamaño_CeldasY/2)+ Tamaño_CeldasY*i, 40,40};
                            Zombies[l].TiempoGolpe=0.0f;
                            Zombies[l].Interactuando=0;

                            if(Zombies[l].Tipo==6){
                                Zombies[l].ColorZombie=ZombieSprite;
                                Zombies[l].Daño=config->dmg_zombie_base;
                                Zombies[l].Velocidad=config->vel_zombie_base;
                            } else if(Zombies[l].Tipo==7){
                                Zombies[l].ColorZombie=FlagZombieSprite;
                                Zombies[l].Daño=config->dmg_zombie_base; //NO ESTA EN LA CONFIGURACION, AÑADIR
                                Zombies[l].Velocidad=config->vel_zombie_flag;
                            } else if(Zombies[l].Tipo==8){
                                Zombies[l].ColorZombie=FootballZombie;
                                Zombies[l].Daño=config->dmg_zombie_base; //NO ESTA EN LA CONFIGURACION, AÑADIR
                                Zombies[l].Velocidad=config->vel_zombie_rugby;
                            }else printf("Zombie no contemplado tipo %d",Zombies[l].Tipo);
                            break;
                        }
                    }
                    rem_zombie(casilla, 0);
                }
            }
        }
    }
}

void ZombieMuerto(ZombieGrafico Zombies[20]){
    for(int i=0;i<20;i++){
        //Si el zombie esta bajo 0 puntos de vida lo desactiva
        if(Zombies[i].Vida<=0 && Zombies[i].Activo){
            printf("DESACTIVANDO Zombie[%d], vida=%d\n",
                   i, Zombies[i].Vida);
            Zombies[i].Activo=false;
            Zombies[i].Fila=0;
            Zombies[i].PosicionX=0.0f;
            Zombies[i].Tipo=0;
            Zombies[i].Vida=0;
            Zombies[i].Velocidad=0;
            Zombies[i].Colision=(Rectangle){0,0,0,0};
            Zombies[i].Daño=0;
            Zombies[i].Detenerse=true;
            Zombies[i].TiempoGolpe=0.0f;
            Zombies[i].Interactuando=0;
        }
    }
}

void ColisionesGuisante(int MaxEntidades,ZombieGrafico Zombies[20],Guisante Guisantes[MaxEntidades],Config *config,Sound Sonido){
    for(int i=0;i<MaxEntidades;i++){
        for(int j=0;j<20;j++){

            if(Zombies[j].Activo){
                if(CheckCollisionRecs(Guisantes[i].Colision,Zombies[j].Colision) && Guisantes[i].activo){
                    Guisantes[i].activo=false;
                    Zombies[j].Vida-=config->dmg_lanzaguisante;
                    PlaySound(Sonido);
                }
            }
        }

        if(Guisantes[i].activo && Guisantes[i].posicion.x>1500){
            Guisantes[i].activo=false;
        }
    }
}

void ColisionesJalapenos(int MaxEntidades,Jalapeno Jalapenos[MaxEntidades], FuegoJalapeno FuegoJalapenos[MaxEntidades],int NumFila, int NumColumna,int MatrizNueva[NumFila][NumColumna],int MatrizJalapenos[NumFila][NumColumna],Sound Sonido){
    for(int i=0;i<MaxEntidades;i++){
        if(Jalapenos[i].Activo && Jalapenos[i].Tiempo>=1){

            for(int j=0;j<MaxEntidades;j++){
                if(FuegoJalapenos[j].Activo==false){
                    FuegoJalapenos[j].Activo=true;
                    FuegoJalapenos[j].Fila=Jalapenos[i].Fila;
                    PlaySound(Sonido);
                    break;
                }
            }

            Jalapenos[i].Activo=false;
            Jalapenos[i].Colision=(Rectangle){0,0,0,0};
            MatrizNueva[Jalapenos[i].Fila][Jalapenos[i].Columna]=0;
            MatrizJalapenos[Jalapenos[i].Fila][Jalapenos[i].Columna]=0;
            Jalapenos[i].Tiempo=0;
        }
    }
}

void DibujarFuegoJalapeno(int MaxEntidades,FuegoJalapeno FuegoJalapenos[MaxEntidades],int CoordXInicio,int CoordYInicio,int Tamaño_CeldasX,int Tamaño_CeldasY,Texture2D FuegoJalapenoSprite,int NumColumnas){
    for(int i=0;i<MaxEntidades;i++){

        if(FuegoJalapenos[i].Activo && FuegoJalapenos[i].Tiempo<=1){
            FuegoJalapenos[i].Tiempo+=GetFrameTime();
            for(int j=0;j<NumColumnas;j++){

                DrawTextureEx(FuegoJalapenoSprite,(Vector2){CoordXInicio+Tamaño_CeldasX*j, CoordYInicio+5+ Tamaño_CeldasY*FuegoJalapenos[i].Fila},0.0f ,1, WHITE);
            }
            FuegoJalapenos[i].Colision=(Rectangle){CoordXInicio, CoordYInicio*(FuegoJalapenos[i].Fila+1),Tamaño_CeldasX*NumColumnas,87};
        } else{
            FuegoJalapenos[i].Tiempo=0;
            FuegoJalapenos[i].Activo=false;
            FuegoJalapenos[i].Colision=(Rectangle){0,0,0,0};

        }
    }
}

void ColisionFuegoJalapenos(int MaxEntidades,ZombieGrafico Zombies[20],FuegoJalapeno FuegoJalapenos[MaxEntidades]){
    for(int i=0;i<20;i++){
        for(int j=0;j<MaxEntidades;j++){
            if(CheckCollisionRecs(FuegoJalapenos[j].Colision,Zombies[i].Colision)){
                //printf("Jalapeño[%d] | Zombie[%d]\n",j,i);
                Zombies[i].Vida-=100000;
            }
        }
        
    }
}

void ColisionPatata(int MaxEntidades,Patata Patatas[MaxEntidades],ZombieGrafico Zombies[20],Texture2D ExplosionSprite, int CoordXInicio, int CoordYInicio, int Tamaño_CeldasX, int Tamaño_CeldasY,Sound Sonido){
    for(int i=0;i<MaxEntidades;i++){
        for(int j=0;j<20;j++){

            if(CheckCollisionRecs(Patatas[i].Colision,Zombies[j].Colision) && Patatas[i].ExplosionActiva==true){
                Patatas[i].ExplosionActiva=false;
                Patatas[i].Tiempo=0;
                Patatas[i].Colision=(Rectangle){0,0,0,0};

                for(int k=0;k<20;k++){
                    if(Zombies[k].Activo && CheckCollisionRecs(Patatas[i].ColisionExplosion,Zombies[k].Colision)){
                        Zombies[k].Vida-=10000;
                        Patatas[i].ExplosionSprite=true;
                        PlaySound(Sonido);
                    }
                }

                Patatas[i].ColisionExplosion=(Rectangle){0,0,0,0};
            }
        }
    }

    for(int i=0;i<MaxEntidades;i++){
        if(Patatas[i].ExplosionSprite){
            Patatas[i].TiempoSprite+=GetFrameTime();
            if(Patatas[i].TiempoSprite<=1){
                DrawTextureEx(ExplosionSprite,(Vector2){CoordXInicio-80+Tamaño_CeldasX*Patatas[i].Columna, CoordYInicio-50+Tamaño_CeldasY*Patatas[i].Fila},0.0f ,1.7, WHITE);
                //DrawTextureEx(Patatas[k].Sprite,(Vector2){CoordXInicio+(Tamaño_CeldasX/2)-42+Tamaño_CeldasX*Patatas[i].Columna, CoordYInicio+5+ Tamaño_CeldasY*Patatas[i].Fila},0.0f ,0.2, WHITE);
            } else{
                Patatas[i].Activo=false;

            }
        }
    }

}

