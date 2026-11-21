
______________________________________________________________________

Imitacion del juego Plantas VS Zombies realizado en el lenguaje de programacion C con la libreria Raylib.

Realizado y compilado originalmente en WSL (Ubuntu). La instalacion de dependencias y configuracion de audio pueden variar.
_______________________________________________________________________

ARCHIVOS:

Codigo:
- DemoPVZ.c
- Funciones_Graficas.c
- guardado.c
- logica_mp.c
- utils_config.c
- utils_map.c
- Funciones_Graficas.h
- guardado.h
- header.h
- logica.h

Sprites:
- Fondo.png
- GirasolSprite.png
- LanzaguisanteSprite.png
- NuezSprite.png
- JalapenoSprite.png
- PatataBoomSprite2.png
- PatataBoomDesactivadaSprite2.png
- FuegoSprite.png
- SolSprite.png
- ZombieBaseSprite.png
- FlagZombieSprite.png
- Pasto_Claro.PNG
- Pasto_Oscuro.PNG
- GirasolCompra.png
- LanzaguisantesCompra.png
- NuezCompra.png
- JalapenoCompra.png
- PatataCompra.png
- LanzaguisantesMejoraCompra.png
- GirasolMejoraCompra.png
- Seleccion.png
- GuisanteSprite.png
- Pow.png
- ContadorSolesSprite.png
- PantallaDerrota.png
- LanzaguisantesMejora.png
- GirasolDoble.png
- FootballZombie.png
- Ganaste.png
- ContadorOleadas.PNG

Audios:
- ZombieBite.ogg
- plant.ogg
- points.ogg
- jalapeno.ogg
- potato_mine.ogg
- shoop.ogg
- splat.ogg
- winmusic.ogg
- losemusic.ogg
- TemaJuego.ogg
____________________________________________________________________________

DEPENDENCIAS NECESARIAS:
- build-essential
- libraylib-dev
- libgl1-mesa-dev
- libx11-dev
- libasound2-dev
- libasound2-plugins
- pulseaudio-utils
_____________________________________________________________________________

PARA COMPILAR:
Primero: gcc -Wall -Wextra -o pvz DemoPVZ.c logica_mp.c utils_map.c utils_config.c guardado.c Funciones_Graficas.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
Despues: ./pvz

___________________________________________________________________________

CONTROLES:
Todo en pantalla se controla clickeando con el click derecho, en caso de no funcionar mover levemente el mouse e intentarlo nuevamente.
Si se desea guardar partida se debe presionar f5 en el momento deseado.