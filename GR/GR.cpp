
//Treads
/*#include <pthread.h>
int thread_flag;
pthread_mutex_t thread_flag_mutex;
void initialize_flag ()
{
pthread_mutex_init (&thread_flag_mutex, NULL);
thread_flag = 0;
}
//Calls do_work repeatedly while the thread flag is set; otherwise spins. 
void* thread_function (void* thread_arg)
{
while (1) {
int flag_is_set;
//Protect the flag with a mutex lock. 
pthread_mutex_lock (&thread_flag_mutex);
flag_is_set = thread_flag;
pthread_mutex_unlock (&thread_flag_mutex);
if (flag_is_set)
do_work ();
//Else don’t do anything. Just loop again.

}
return NULL;
}
// Sets the value of the thread flag to FLAG_VALUE.
 
void set_thread_flag (int flag_value)
{
// Protect the flag with a mutex lock. 
pthread_mutex_lock (&thread_flag_mutex);
thread_flag = flag_value;
pthread_mutex_unlock (&thread_flag_mutex);
}
*/


#include "L64/AXL64.h"
#include "GR.h"

#include "../../AXIS/LIB/AX.h"

//#include "TESTFEATURES.h"


int main(int argc, char* argv[]) {
   
    //AXIS INIT
int idse= ISE ();
int idsmi=ISMI ();
int idsmd=ISMD ();

int idsnc=SNCI();//sems en 0 supuestamente, libres

 AXH AXIS(idse,idsmi,idsmd/*,idsnc*/);
 //AXIS INIT
 
	
	ENV ENV1;//Entorno 1
	CAM CAM1;//Camara orbital 1

	//TESTFEATURES
	
	
	
	TDSCEN TOOL;
TOOL.TDI("RESOURCES/GEOMETRIES/tool.blend");

GRAPH GR;
GR.color[0]=0.011; GR.color[1]=0.793; GR.color[2]=0.6914f;
for(float i=0;i<20;i+=0.01){
GR.X.push_back(i);
GR.Y.push_back(sin(i));}
   

	
	//MATRIX_2D IMGEN (40,40,1);	
	//VBO VBO1;

	//TESTFEATURES


	//Graphic resources initializer.
	TTF_Font *HelvRom_30 = TTF_OpenFont("RESOURCES/FONTS/HelveticaLTStd-Roman.otf", 30);
        TTF_Font *HelvRom_90 = TTF_OpenFont("RESOURCES/FONTS/HelveticaLTStd-Roman.otf", 90);
        
	const SDL_Color AXgreen = { 9,203,177 };
	const SDL_Color AXwhite = { 230,230,230 };
	const SDL_Color AXgrey = { 120,120,120 };
	const SDL_Color AXblack = { 5,5,5 };
	
	TXT TEXTO;
	long textoc = 0;
        std::string TEXT;
        
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
                AXIS.rD();
                TEXT.clear();
                TEXT+=std::to_string(AXIS.X.A);
		//snprintf(Text1, 200,"%d",AXIS.X.S);
                
                GR.DU(AXIS.X.A);
                
                PLUS.U(ENV1.moscx,ENV1.moscy, ENV1.mosdx,ENV1.mosdy, ENV1.mosx, ENV1.mosy, ENV1.rclick, ENV1.lclick);
                //PLUS.
                DBST.clear();
                DBST+=std::to_string(PLUS.nLclicks);
                
			
	
            }
            
            if (ENV1.DRW_I()) {ENV1.R_DRW_I();//Dibujado de interfaz del entorno 
		

		//IMGEN.DMATRIX();

		TEXTO.D(HelvRom_30,AXwhite,TEXT);
                
                
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
                
                glTranslatef(0, 60, 0);
                glColor3f( 0.011f,0.793f,0.6914f);
                glScalef(40,0.005,1); 
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
