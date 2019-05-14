#!/bin/bash 
#cd /
#cd home/axs/DEV/LIB/GR

#konsole --noclose -e sh -c "cd / &&
#konsole  -e sh -c "
cd / &&
cd home/mrq/DEV/LIB/NN &&
g++ NN_GUI.cpp -std=c++11 -lpthread -lSDL2 -lSDL2_image -lSDL2_ttf -lGL -lGLU -lglut -lassimp -lGLEW -o NN_GUI &&
./NN_GUI
#"
 

