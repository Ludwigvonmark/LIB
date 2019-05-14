#!/bin/bash 
#cd /
#cd home/axs/DEV/LIB/GR

#konsole --noclose -e sh -c "cd / &&
konsole  -e sh -c "
cd / &&
cd home/axs/DEV/LIB/GR &&
g++ GR.cpp -std=c++11 -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lglut -lassimp -lGLEW -o GR &&
./GR
 
"
