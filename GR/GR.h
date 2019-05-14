#ifndef AXENGINE_H_INCLUDED
#define AXENGINE_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//#include "AX3D/GLee.h"

#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <assimp/Importer.hpp>
#include <assimp/cimport.h>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

#include <stdint.h>

#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <utility>

SDL_GLContext Context;
SDL_Event Event;

#define _USE_MATH_DEFINES

//#include"../MATH.h"
#include "G_LIB/GEO_2D.h"
#include "G_LIB/RASTER_LOADER.h"
#include "G_LIB/UI_UTILITIES.h"
#include "G_LIB/GRAPH.h"

#include "G_LIB/CAM.h"
#include "G_LIB/3DL_LEGACY.h"

//#include "G_LIB/VBO.h"


class ENV {



	bool EXEC = true;

	bool UUI = true;
	bool DUI = true;

	bool U3D = true;
	bool D3D = true;

	SDL_Window* Window = NULL;

	public:
	int SCREEN_WIDTH = 1000; int SCREEN_HEIGHT = 480;


		int mosx, mosy, mosdx, mosdy, moscx, moscy;
		bool rclick = false;
		bool lclick = false;
		bool mclick = false;
		bool released = false;
                
        ICONST ICON;

	ENV() {
		Window = NULL;
		SDL_Init(SDL_INIT_EVERYTHING);
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);


		
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );

		Window = SDL_CreateWindow("MRQS FINANCIAL COMPUTE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED
			, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		SDL_SetWindowMinimumSize(Window, 100, 100);

		//SDL_SetWindowBordered(Window,SDL_FALSE);
		SDL_SetWindowIcon(Window, ICON.APP);
		SDL_GL_SetSwapInterval(1);
		Context = SDL_GL_CreateContext(Window);
		glClearColor(0.05, 0.05, 0.05, 1.0);
		glMatrixMode(GL_MODELVIEW);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 1000.0);
		glMatrixMode(GL_MODELVIEW);
		//glEnable(GL_CULL_FACE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		//glEnable(GL_LIGHT1);

		float l0pos[] = { 20,20,20,1 };

		glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
		float ldif[] = { 1.0,0.9,1.0,1.0 };
		glLightfv(GL_LIGHT0, GL_DIFFUSE, ldif);
		float lamb[]={0.2,0.2,0.2,1.0};
		glLightfv(GL_LIGHT0,GL_AMBIENT,lamb);
		//glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
	}

	~ENV() {
		SDL_DestroyWindow(Window);
		IMG_Quit();	TTF_Quit(); SDL_Quit();
		std::cout << "Exit succesfuly" << std::endl; //return 0;
	}

	void EVE() {
		mosdx = mosx; mosdy = mosy;
		moscx = 0; moscy = 0;

		while ((SDL_PollEvent(&Event) != 0)) {
			
				
			if (Event.type == SDL_MOUSEWHEEL) {
				if (Event.wheel.type) {
					moscx = Event.wheel.x;
					moscy = Event.wheel.y;
				}
			}
			SDL_GetMouseState(&mosx, &mosy);
			mosy = SCREEN_HEIGHT - mosy;
			
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
				lclick = true; rclick = false; mclick = false;
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
				rclick = true; lclick = false; mclick = false;
			}
			else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
				mclick = true; rclick = false; lclick = false;
			}
			else { rclick = false; lclick = false; mclick = false; }

			/*if (Event.type == SDL_TEXTINPUT) {
				//T.edit=e.edit.text;
				//strcat(T.edit, e.text.text);
				//T.edit= e.text.text;
			}*/



			/*switch (Event.type) {
			case SDL_FINGERDOWN:
			{
				SDL_TouchFingerEvent tfinger = Event.tfinger;
				printf("FingerID: %i", tfinger.fingerId);
				std::cout << "Finger: " << static_cast<int>(tfinger.fingerId)
					<< " pressed with pressure: " << tfinger.pressure << std::endl;
				std::cout << "Current position is: " << tfinger.x
					<< ", " << tfinger.y << std::endl;
			}
			break;
			case SDL_FINGERUP:
			{
				SDL_TouchFingerEvent tfinger = Event.tfinger;
				std::cout << "Finger: " << static_cast<int>(tfinger.fingerId)
					<< " released" << std::endl;
			}
			break;
			case SDL_FINGERMOTION:
			{
				SDL_TouchFingerEvent tfinger = Event.tfinger;
				std::cout << "Finger: " << static_cast<int>(tfinger.fingerId)
					<< " moved with vector ("
					<< tfinger.dx << ", " << tfinger.dy
					<< ") with pressure: " << tfinger.pressure << std::endl;
				std::cout << "Current position is: " << tfinger.x
					<< ", " << tfinger.y << std::endl;
			}

			}*/




				
			if (Event.type == SDL_WINDOWEVENT) {
				switch (Event.window.event) {
				case SDL_WINDOWEVENT_RESIZED:

					SCREEN_WIDTH = Event.window.data1;
					SCREEN_HEIGHT = Event.window.data2;
					glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
				}}

			if (Event.type == SDL_QUIT)
			{
				EXEC = false;
				break;
			}
		}
		}//event end

	bool EXECUT() {//ejecución del programa
		return EXEC;
	}
	
	
	bool UPD_3D() {//actualización de gráficos
		return U3D;
	}
	bool DRW_3D() {
		return D3D;
	}
	void R_DRW_3D() {//Rutinas de dibujado de gráficos
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_COLOR_MATERIAL);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
		gluPerspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 1.0f, 10000.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
                
                glEnable(GL_LIGHTING);
                
	}
	
	

	bool UPD_I() {//Actualización de la interfáz
		return UUI;
	}
	bool DRW_I() {
		return DUI;
	}
	void R_DRW_I() {//Rutinas de dibujado de interfáz
		glLoadIdentity();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, ((float)SCREEN_WIDTH), 0, ((float)SCREEN_HEIGHT), -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
	}

	

	void SWAP() {
		SDL_GL_SwapWindow(Window);
	}

};

#endif
