

#include "../GR/L64/AXL64.h"
#include "../GR/GR.h"
#include "../CSV.hpp"
#include "../LINUX/SML.h"
#include "NN.hpp"

int main(int argc, char* argv[]) {	
	ENV ENV1;//Entorno 1
	CAM CAM1;//Camara orbital 1

	TDSCEN TOOL;
TOOL.TDI("../GR/RESOURCES/GEOMETRIES/tool.blend");

CSV fnD;//fn, data, for graphic
SMLL NNSM;
NNSM.AXSMZd=10000000;
NNSM=SMLL(100,2000);  

 // fnD.LCSV("SF_TST.csv");

    NNSM.R();
  fnD.RCD(NNSM.AXSM);

GRAPH GR;
GR.color[0]=0.011; GR.color[1]=0.793; GR.color[2]=0.6914f;
for(int i=0;i<fnD.DATA.size();i+=1){
GR.X.push_back(i);
GR.Y.push_back(fnD.DATA[i][1]);
    //std::cout<<fnD.LDATA[0][i]<<std::endl;
}
GR.ND();
      /* for (int ind=0;ind<inId.size();ind++){
                    cTD.push_back(TD.LDATA[Id][inId[ind]]);
                }*/
   

	
	//MATRIX_2D IMGEN (40,40,1);	
	//VBO VBO1;

	//TESTFEATURES


	//Graphic resources initializer.
	TTF_Font *HelvRom_30 = TTF_OpenFont("../GR/RESOURCES/FONTS/HelveticaLTStd-Roman.otf", 30);
        TTF_Font *HelvRom_90 = TTF_OpenFont("../GR/RESOURCES/FONTS/HelveticaLTStd-Roman.otf", 90);
        
	const SDL_Color AXgreen = { 9,203,177 };
	const SDL_Color AXwhite = { 230,230,230 };
	const SDL_Color AXgrey = { 120,120,120 };
	const SDL_Color AXblack = { 5,5,5 };
	
	TXT TEXTO;
	long textoc = 0;
       // std::string TEXT;
        
        	TXT DBT;
        std::string DBST;
        
        TXT GRC;
        std::string GRCT;
for(int c=0;c<50;c++)GRCT+=" . ";

BTN PLUS;
	//char Text1[2000];

//	D2_GRAFIC GRAPH_TEST;

	//TESTFEATURES


	while (ENV1.EXECUT()) {
		ENV1.EVE();//Eventos del entorno
                
                
                
            if (ENV1.UPD_3D()) {//Actualizaíón de gráficos del entorno 
		
                        CAM1.U(ENV1.moscy, ENV1.mosdx, ENV1.mosdy, ENV1.mosx, ENV1.mosy, ENV1.rclick, ENV1.mclick);
                       
                        
                        
            }
            
            if (ENV1.DRW_3D()) {ENV1.R_DRW_3D();//Dibujado de gráficos del entorno 
		
		CAM1.D();
                
                    TOOL.TDD();
                    
                    glRotatef(90,1,0,0);
                 
                    
		
		glTranslatef(0, 0, 0.0f);
		glColor3f(1.0, 1.0, 1.0);
		//glTranslatef(250, 250, -100.0f);
		//DRect(1000, 1000);
            }
                
                
                
                
		
            if (ENV1.UPD_I()) {//Actualización interfaz del entorno 
			//IMGEN.UMATRIX_pro(); 

		//	GRAPH_TEST.UP_2D();
                
                //TEXT.clear();
                //TEXT+=std::to_string("1");
		//snprintf(Text1, 200,"%d",AXIS.X.S);
                
               // GR.DU(1);
                
                PLUS.U(ENV1.moscx,ENV1.moscy, ENV1.mosdx,ENV1.mosdy, ENV1.mosx, ENV1.mosy, ENV1.rclick, ENV1.lclick);
                //PLUS.
                DBST.clear();
                DBST+=std::to_string(PLUS.nLclicks);
                
			
	
            }
            
            if (ENV1.DRW_I()) {ENV1.R_DRW_I();//Dibujado de interfaz del entorno 
		

		//IMGEN.DMATRIX();

		//TEXTO.D(HelvRom_30,AXwhite,TEXT);
                
                
                glTranslatef(0, 40, 0);               
                glColor3f(0.2,0.2,0.2);
                DRect(ENV1.SCREEN_WIDTH, 120);
                
                DBT.D(HelvRom_30,AXwhite,DBST);
                
                glPushMatrix();
                glTranslatef(0,-3, 0); 
                
                GRC.W=ENV1.SCREEN_WIDTH;
                
                       // glLoadIdentity();
                for (int y=0;y<10;y++){
                    
                   // for(int x=0;x<100;x++){
                        
                         glTranslatef(0,10, 0); 
                        
                        GRC.D(HelvRom_30,AXblack,GRCT);
                   // }
                    
                }
                
                
                glPopMatrix();
                
                glTranslatef(0, 0, 0);
                glColor3f( 0.011f,0.793f,0.6914f);
                glScalef(ENV1.SCREEN_WIDTH,ENV1.SCREEN_HEIGHT-50,1); 
                GR.D();
                 
                 
                 
                 
                 
                 glLoadIdentity();
                 glTranslatef(PLUS.rDrag[0],PLUS.rDrag[1], 0);
                 
                 if(PLUS.over){ glColor3f(0.8,0.5,0.2);
                DRect(/*PLUS.bon[0],PLUS.bon[2]*/100,100);}
                
                       if(PLUS.clickl){ glColor3f(0.5,0.8,0.2);
                DRect(/*PLUS.bon[0],PLUS.bon[2]*/80,80);}
                
                 if(PLUS.CLICKL){ glColor3f(0.5,0.5,0.2);
                DRect(/*PLUS.bon[0],PLUS.bon[2]*/50,50);}
                
                 if((PLUS.nLclicks%2)!=0){ glColor3f(0.7,0.3,0.5);
                DRect(/*PLUS.bon[0],PLUS.bon[2]*/30,30);}
                
                if(PLUS.drag){ glColor3f(0.9,0.3,0.9);
                DRect(PLUS.rDrag[0],PLUS.rDrag[1]);}
                
                glColor4f(0.2,0.5,0.8,0.5);
                DRect(PLUS.bon[1]-PLUS.bon[0],PLUS.bon[3]-PLUS.bon[2]);
                //DRect(25,25);
                
                 PLUS.D(HelvRom_90,AXwhite,"+");

                 
                 
		//glTranslatef(0, 100, 0);
	//	VBO1.D();
	//	GRAPH_TEST.DR_2D();
	//	GRAF.DG_2D();

            }



		ENV1.SWAP();
	}

	return 0;}
