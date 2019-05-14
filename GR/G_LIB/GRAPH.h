#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

class GRAPH{
    
    public:
        //Boundaries
        int BX0=0;//Minimum x coordinate
        int BXF=0;//Maximum x coordinate
        int BY0=0;
        int BYF=0;
        //Boundaries
        
        //Graph control variables
        bool top=false;//if the mous on top of the graph
        float Xsca=1;//Escala x
        float Xtra=0;//Traslacion x
        float Ysca=1;
        float Ytra=0;
        //Graph control variables

std::vector <float> X;
std::vector <float> Y;
std::vector <std::vector<float>> Z;

float Xmin=-300;
float Xmax=300;
float Xdom=600;//Espacio en el que representar el gráfico

float Ymin=-150;
float Ymax=150;
float Ydom=300;//Espacio en el que representar el gráfico

float Zmin=0;
float Zmax=0;
float Zdom=0;//Espacio en el que representar el gráfico

double MXx=-1e200;
double MNx=1e200;
double RGx=1e200;

double MXy=-1e200;
double MNy=1e200;
double RGy=1e200;

double ZxP=0;
double ZyP=0;

bool lines=true;
bool surf=false;



	float color[3]={0,0,0};

	GRAPH() {
		lines=true;
	}

	~GRAPH() {
    X.clear();
    Y.clear();
    Z.clear();
	}

	void DU(float variable) {//Actualización dinamica de graficos, almacena datos de variable en orden.
Y[Y.size()-1]=variable;
for(int n=1;n<Y.size();n++){
    Y[n-1]=Y[n];
}
	}
	
		void DU(float Xv, float Yv) {//Actualización dinamica de graficos, almacena datos de variable en orden.
Y[Y.size()-1]=Yv;
for(int n=1;n<Y.size();n++){
    Y[n-1]=Y[n];
}
	}
	
void NDx(){//Normalize X data
            MXx=-1e200;
            MNx=1e200;
            RGx=1e200;
    
        for(int i=0;i<X.size();i++){//Obtain de maximuns and minimun

                if(MXx<X[i]){
                    MXx=X[i];
                }
                if(MNx>X[i]){
                     MNx=X[i];
                }
               
            }
        RGx=MXx-MNx;
        ZxP=-MNx/RGx;
}

void NGx(){//Normalize X graph        
        for(int c=0;c<X.size();c++){
                X[c]=(X[c]-MNx)/(RGx);                       
        }
            //Normalize predict from
}

void NDy(){//Normalize Y data
            MXy=-1e200;
            MNy=1e200;
            RGy=1e200;
    
        for(int i=0;i<Y.size();i++){//Obtain de maximuns and minimun

                if(MXy<Y[i]){
                    MXy=Y[i];
                }
                if(MNy>Y[i]){
                     MNy=Y[i];
                }
               
            }
        RGy=MXy-MNy;
        ZyP=-MNy/RGy;
}

void NGy(){//Normalize Y graph        
        for(int c=0;c<Y.size();c++){
                Y[c]=(Y[c]-MNy)/(RGy);                       
        }
            //Normalize predict from
}

void UB(){//Rutina de actualización de los limites visuales en pantalla del grafico
    //Obtiene los datos rtelativos al tamaño y posición del grafico.
                GLfloat mtxpos[16];//Almacena la posición actual recogida de openGL
                glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
                BX0=(int)mtxpos[12];
                BY0=(int)mtxpos[13];
                BXF=(int)mtxpos[0]+BX0;
                BYF=(int)mtxpos[5]+BY0;
                
                
		//bon[0] = mtxpos[12];
		//bon[2] = mtxpos[13];
                /*for (int i = 0; i < 4; i++) {
  for (int j = 0; j < 4; j++) {
    printf("%f [%i] ", mtxpos[j * 4 + i],j * 4 + i);
  }
  printf("\n");
}
printf("\n");//*/
                
}

void CG(std::vector<int> mous, std::vector<bool> cmous){//Graph control routine
    if(mous[0]>=BX0 && mous[0]<=BXF && mous[1]>=BY0 && mous[1]<=BYF){
        //printf("on\n");
        top=true;
        Xsca+=mous[5]*1;
        if(Xsca<=1){
            Xsca=1;
        }
        Xtra=1-Xsca;
        
    }
    else{
        top=false;
    }
}

	void D(/*float Xsiz=Xdom, float Ysiz=Ydom, float Zsiz=Zdom*/ ) {//Rutinas de dibujado del grafico, Para el tamaño dado;
if(top){
    glLineWidth(3);
}
else{
    glLineWidth(1);
}
		glTranslatef(Xtra, Ytra, 0);
                glScalef(Xsca,Ysca,1);
		glColor3f(color[0], color[1], color[2]);
                
		glBegin(GL_LINE_STRIP);
//Gráfico bidimensional
                    for (int x=0;x<X.size();x++){
                        glVertex3f(X[x], Y[x],0);
                        
                    }
		glEnd();
                		glColor3f(1,1,1);
	}
	
	
	
};


#endif
