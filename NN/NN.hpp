#ifndef NN_dbg_H_INCLUDED
#define NN_dbg_H_INCLUDED

//Neural Net lib

#include <vector>
#include <math.h>   // exp
#include <stdlib.h> // rand
#include <time.h>
#include <functional>

#include <fstream>
#include <string>

#include <algorithm>

#include <iostream> //cout,cin

#include "../PARSR/CSV.hpp"
#include "../MATH/MATH.h"
//#include "../SML.h"
//#include "../SNC.h"

#include "NO.hpp"
#include "EV.hpp"


class NNS {//Neural Net sistem routines

public:
    int nIn=0;
    int nOut=0;
    
    NN NEURAL;//Red neural
    EVOL EV;//Evolution routines
    
    CSV TD;//Datos de entrenamiento
    CSV PD;//Datos para prediccion
    
    std::vector<std::vector<double>> TDv;//Datos para entrenamiento
    std::vector<std::vector<double>> PDv;//Datos de predicciones correctas para error cuadratico
    
    CSV SC;//Configuraciones salvadas
    
    //CSV CBND;//Current best neural config
    //CSV CND;//Current neural config, for improvment
                
    std::vector<int> inId;//Identificador de datos de entrenamiento de entrada
    std::vector<int> outId;//Identificador de datos de entrenamiento de salida
    std::vector<double> cTD;//Datos de entrada entrenamiento
    std::vector<double> cTR;//Resultados de entrenamiento para calcular el error, cada componente del vector se corres ponde con cadauna de las salidas de la red
    double MINGE=std::numeric_limits<double>::max();
    double ME=std::numeric_limits<double>::max();
    double MXE=std::numeric_limits<double>::max();
    
    double SGRN=std::numeric_limits<double>::max();
    double GRN=std::numeric_limits<double>::max();
    
    std::vector<double> cPD;//Datos de entrada de prediccion
        
   /* NNS(std::string TRPATH, std::string NDPATH,std::vector<int> InId, std::vector<int>OutId):TD(TRPATH),SC(NDPATH){
        NEURAL=NN();
        inId=InId;
        outId=OutId;
        nIn=InId.size();
        nOut=OutId.size();
        EV=EVOL();
        
         srand((unsigned)time(NULL));//generado aleatorio
        }*/
      
       NNS(/*,std::string NDPATH*/)/*:SC(NDPATH)*/{
        NEURAL=NN();
        SC=CSV(16);
        inId.clear();
        /*for (int i=0;i<TrainingD[0].size();i++){
            inId.push_back(i);
        }*/
        //TDv=TrainingD;
        outId.clear();
        /*for (int i=0;i<ResultD[0].size();i++){
            outId.push_back(i);
        }*/
        /*PDv=ResultD;
        nIn=TrainingD[0].size();
        nOut=ResultD[0].size();*/
        EV=EVOL();
        
        srand((unsigned)time(NULL));//generado aleatorio
        
    }
   
    NNS(std::vector<std::vector<double>>TrainingD, std::vector<std::vector<double>>ResultD/*,std::string NDPATH*/)/*:SC(NDPATH)*/{
        NEURAL=NN();
        SC=CSV(16);
        inId.clear();
        for (int i=0;i<TrainingD[0].size();i++){
            inId.push_back(i);
        }
TDv=TrainingD;
        outId.clear();
        for (int i=0;i<ResultD[0].size();i++){
            outId.push_back(i);
        }
PDv=ResultD;
        nIn=TrainingD[0].size();
        nOut=ResultD[0].size();
        EV=EVOL();
        
        srand((unsigned)time(NULL));//generado aleatorio
        
    }
        
      //  ~NNS(){}
        
    void PINIT(std::vector<std::vector<double>>TrainingD, std::vector<std::vector<double>>ResultD){//Pseudo inicializador, introduce los datos de predicción y entrenamiento
                inId.clear();
        for (int i=0;i<TrainingD[0].size();i++){
            inId.push_back(i);
        }
TDv=TrainingD;
        outId.clear();
        for (int i=0;i<ResultD[0].size();i++){
            outId.push_back(i);
        }
PDv=ResultD;
        nIn=TrainingD[0].size();
        nOut=ResultD[0].size();
    }
        
///Algoritmos y rutinas de manejo de archivos
       
    //Rutinas de debugueado;
    void DBG_NND(){//Muestra en consola los datos relativos a la red neuronal
        //dbg
            std::cout<<"--------DBG_NND-"<<std::endl;
            std::cout<<"Topolog: ";
            for(int t=0;t<NEURAL.T.size();t++){std::cout<<NEURAL.T[t]<<" ";}
            std::cout<<std::endl;
            std::cout<<"Weights: ";
            for(int w=0;w<NEURAL.W.size();w++){std::cout<<NEURAL.W[w]<<" ";}
            std::cout<<std::endl;
            std::cout<<"--------DBG_NND-"<<std::endl<<std::endl;
            //dbg*/
    }
    //Rutinas de debugueado
    void LND(){//Carga la configuracion de la red almacenada CSV SC
            
            if(SC.DATA.size()==0){std::cout<<"No neural data"<<std::endl;}
            
            else{
                //dbg
                //std::cout<<"NEURAL SAVED DATA"<<std::endl;
                
                NEURAL.T.clear();
                NEURAL.W.clear();
                
                //std::cout<<"ERRORS: ";
                //dbg
                
                //Primera linea ERRORES y gradiente
                    MINGE=SC.DATA[0][0];//Error máximo de la mejor configuración en su primera etapa de entranamiento
                    ME=SC.DATA[0][1];//Error máximo / numero de datos usados en el entrenamiento
                    
                    SGRN=SC.DATA[0][2];//Gradiente del error
                    //dbg
                   // std::cout<<SC.DATA[0][0]<<" ";
                  // std::cout<<std::endl;
                    //dbg
                
                                //dbg
                //std::cout<<std::endl;
                //std::cout<<"TOPOLOG: ";
                //dbg
                
                for(int t=0;t<SC.DATA[1].size();t++){//Segunda linea topologia
                    NEURAL.T.push_back(SC.DATA[1][t]);
                    
                    //dbg
                   // std::cout<<SC.DATA[1][t]<<" ";
                    //dbg
                }
                
                //dbg
               // std::cout<<std::endl;
              //  std::cout<<"WEIGTH: ";
                //dbg
                
                for(int w=0;w<SC.DATA[2].size();w++){//Tercera linea pesos
                    NEURAL.W.push_back(SC.DATA[2][w]);
                    
                    //dbg
                  //  std::cout<<SC.DATA[2][w]<<" ";
                    //dbg
                }
                
                //dbg
                //std::cout<<std::endl;
                //dbg*/
            }
    
}
        
    void SND(){//Salva al archivo la configuracion de la red
            //dbg
            //std::cout<<"Saving NND"<<std::endl;
            //dbg
        if(MXE>0&&GRN>0){
            SC.DATA.clear();
            
            SC.DATA.push_back({MXE,MXE/PDv.size(),GRN});//Datos de configuracion
            std::vector<double> Td(NEURAL.T.begin(), NEURAL.T.end());
            SC.DATA.push_back(Td);
            SC.DATA.push_back(NEURAL.W);
        }
        else{
            std::cout<<"NN ERR; SAVE NOT AVALIABLE"<<std::endl;
        }

            
            //SC.SCSV();
        }
    
///Algoritmos y rutinas de manejo de archivos
        
///Algoritmos y rutinas de entrenamiento
       
    void NWG(){//Generador de pesos sin pesos previos
           
        NEURAL.T.push_back(nIn);//numero de entradas
        NEURAL.T.push_back(1);//una capa de neuronas ocultas, con n neuronas
        NEURAL.T.push_back(nOut);//numero de salidas

        int ns = NEURAL.T[0];// cacluar el numero de sinapsis, y crea los pesos
        for (int i = 1; i < NEURAL.T.size(); i++) {
            ns += NEURAL.T[i] * NEURAL.T[i - 1];
            //std::cout << ns << std::endl;
        }//fin del calculo del numero de sinapsis
        for (int i = 0; i < ns-NEURAL.T[0]; i++) {//crea aleatoriamente los pesos de las sinspsis.
            NEURAL.W.push_back(GRNG(1,-1));
            //std::cout << weigths[i] << ", ";
        }

    }
    
    void WG(){//Generador de pesos para una nueva topologia dada utilizando pesos anteriores
           int ns = NEURAL.T[0];// cacluar el numero de sinapsis
            for (int i = 1; i < NEURAL.T.size(); i++) {
                ns += NEURAL.T[i] * NEURAL.T[i - 1];
               // std::cout << ns << std::endl;
            }//fin del calculo del numero de sinapsis
            
       
            //Algoritmo simpe
            if(ns-NEURAL.T[0]>=NEURAL.W.size()){
                for (int i =NEURAL.W.size(); i < ns-NEURAL.T[0]; i++) {//crea aleatoriamente los pesos de las sinspsis.
                    NEURAL.W.push_back(GRNG(1,-1));
                //std::cout << weigths[i] << ", ";
            }
                    
        }
        else{
                            //NEURAL.W.clear();
                            for (int i =NEURAL.W.size(); i > ns-NEURAL.T[0]; i--) {//elimina los pesos sobrantes
                NEURAL.W.pop_back();
        }
                
        }
            //Algoritmo simple
    }
    
     void WGA(){//Generador de pesos para una nueva topologia dada utilizando pesos aleatorios
           int ns = NEURAL.T[0];// cacluar el numero de sinapsis
            for (int i = 1; i < NEURAL.T.size(); i++) {
                ns += NEURAL.T[i] * NEURAL.T[i - 1];
               // std::cout << ns << std::endl;
            }//fin del calculo del numero de sinapsis
            
            NEURAL.W.clear();
            //Algoritmo simple
        for (int i = 0; i < ns-NEURAL.T[0]; i++) {//crea aleatoriamente los pesos de las sinspsis.
                NEURAL.W.push_back(GRNG(1,-1));
            //NEURAL.W.push_back(0);
            //std::cout << weigths[i] << ", ";
        }
    }
       
    void INN(){//Inicializa los datos de la red para una topologia dada

        if(NEURAL.W.empty()){
            NWG();
            
        }//No existen pesos previos
       else{
           WG();
           
        }           //Existen pesos previos
        
        NEURAL.INN(NEURAL.T,NEURAL.W);
    }
    
       
    void UT(int Id ){//Recoge los datos de entrenamiento de un vector y los mete a los vectores de entrenamiento, para bases de datos de quandl
            
            //dbg
            //std::cout<<"Correct"<<std::endl; 
            //dbg
            
            if(inId.size()!=nIn)std::cout<<"Numero de datos de entrada no coincide con el numero de neuronas de entrada"<<std::endl;
            else{
                
                cTD.clear();
                for (int ind=0;ind<inId.size();ind++){
                    cTD.push_back(TDv[Id][inId[ind]]);
                }
                
            }
            
            if(outId.size()!=nOut)std::cout<<"Numero de datos de salida no coincide con el numero de neuronas de salida"<<std::endl;
            else{
                
                cTR.clear();
                for (int outd=0;outd<outId.size();outd++){
                    cTR.push_back(PDv[Id][outId[outd]]);
                }
                
            }
            NEURAL.UD(cTD);
           /* //dbg
            std::cout<<"UT:"<<std::endl<<"cTD= ";
            for(int c=0;c<cTD.size();c++){std::cout<<cTD[c]<<" ";}
            std::cout<<"cTR= ";
            for(int r=0;r<cTR.size();r++){std::cout<<cTR[r]<<" ";}
            std::cout<<std::endl;
            //dbg */
            
        }
        
    void UP(int Id ){//Recoge los datos de predicción de un vector y los mete a los vectores de la red neuronal
            
            //dbg
            //std::cout<<"Correct"<<std::endl; 
            //dbg
            
            if(inId.size()!=nIn)std::cout<<"Numero de datos de entrada no coincide con el numero de neuronas de entrada"<<std::endl;
            else{
                
                cTD.clear();
                for (int ind=0;ind<inId.size();ind++){
                    cTD.push_back(TDv[Id][inId[ind]]);
                }
                
            }
            
  

            NEURAL.UD(cTD);
            //dbg
            /*std::cout<<"UT:"<<std::endl<<"cTD= ";
            for(int c=0;c<cTD.size();c++){std::cout<<cTD[c]<<" ";}
            std::cout<<"cTR= ";
            for(int r=0;r<cTR.size();r++){std::cout<<cTR[r]<<" ";}
            std::cout<<std::endl;
            //dbg*/
            
        }

    double LCEF(std::vector<double>w){//Local cuadratic error function
            double CE = 0;
            NEURAL.W=w;
            NEURAL.FRW();
            
                //dbg
               // std::cout<<"LCEF"<<std::endl;
                //dbg
                
            for (unsigned int i = 0; i < NEURAL.NNOUT.size(); i++) {
                
               /*//dbg

                std::cout<<"cTR[i]: "<<cTR[i]<<std::endl;
                std::cout<<"NEURAL.NNOUT[i]: "<<NEURAL.NNOUT[i]<<std::endl;

                //dbg*/
        
                CE += (pow(cTR[i] - NEURAL.NNOUT[i], 2));
                
            }
            /*//dbg
             std::cout<<"CE: "<<CE<<std::endl;
                             std::cout<<"-------------"<<std::endl;
            //dbg*/
            return CE;
    }


    double GCEF(std::vector<double>w){//Global cuadratic error function 
           double CE = 0;
           NEURAL.W=w;
            for(int nd=0;nd<TDv.size();nd++){//Iterador por todos los datos de entrenamiento disponibles
                UT(nd);//La entrada de esta funcio ha de introducirse en unos vectores que se modifiquen al principio del programa
            
                NEURAL.FRW();

                for (unsigned int i = 0; i < NEURAL.NNOUT.size(); i++) {
                    CE +=(pow(cTR[i] - NEURAL.NNOUT[i], 2));
                }

            }
            return CE;
    }
   
    double GCEFD(int wId){//Derivada parcial para el peso wId de la función de error cuadrático
       
    }
   
   void NTRL(int nIteraciones){//Rutinas de entrenamiento de la red neural usando errores locales
        double cefn;
        for(int iters=0;iters<10;iters++){
            for(int nd=1;nd<TD.DATA.size()-1;nd++){//Iterador por todos los datos de entrenamiento disponibles
                UT(nd);
                //UTD();*/
                std::function<double(std::vector<double>)> f = std::bind(&NNS::LCEF, this,std::placeholders::_1);
                NEURAL.W=NEUR_GDO(f,NEURAL.W,nIteraciones,0.1e-100);
             }
        }
    }
        
    void NTRG(int nIteraciones,double Terr=1e-100,double GrdLmt=1e4, double s=1.001, double B=0.05255){//Rutinas de entrenamiento de la red neural usando errores globales
            std::function<double(std::vector<double>)> f = std::bind(&NNS::GCEF, this,std::placeholders::_1);
            NEURAL.W=NEUR_GDO(f,NEURAL.W,nIteraciones,Terr,GrdLmt,s,B,&GRN,&MXE);
        }    

    void EVO(){//Evolution routines
            EV.GNT(NEURAL.T);
            int nINSS=NEURAL.T[0];
            int nOUTT=NEURAL.T[NEURAL.T.size()-1];
            NEURAL.T.clear();
            NEURAL.T.push_back(nINSS);
            for (int ntt=0;ntt<EV.NT.size();ntt++)NEURAL.T.push_back(EV.NT[ntt]);
            NEURAL.T.push_back(nOUTT);

            INN();
    }
       
///Algoritmos y rutinas de entrenamiento
        
///Algoritmos y rutinas de uso de la red

///Algoritmos y rutinas de uso de la red
        
///Rutinas de uso simplificadas

    void LrnEv(double TRGERR,int ftI,int evI,double GrdLmt=1e4, double s=1.001, double B=0.05255){//Algoritmo de entrenamiento con evolución version
     //MINGE=1;
     for(int i=0;(i<evI)&&(MXE>TRGERR);i++){ 
         MXE=1e100;
            //DBG_NND();     
         //while(MXE>TRGERR){
            //std::cout<<"fn: "<< std::setprecision(20)<<GCEF(NEURAL.W)<<std::endl<<std::endl;
            NTRG(ftI,TRGERR,GrdLmt);
            //std::cout<<"fn: "<< std::setprecision(20)<<GCEF(NEURAL.W)<<std::endl<<std::endl;
            
            ME=MXE/PDv.size();
            double cefn;

            //Exportación de los datos de la red
        
            SND();
            //
            
           // std::cout<<std::endl<<"CHECK----1----"<<std::endl;
            //DBG_NND();
            
            //Evolution routines//BUG _ LA EVOLUCIÖN SI ES EJECUTADA AL FINAL DEL CICLO CAMBIA LOS DATOS DE LA RED Y LAS CONSIGUIENTES PREDICCIONES SE HACEN SIN ENTRENAMIENTO, Para realizar predicciones acontinuacion del entrenamiento con evolución se ha de usar la función LND() para cargar la ultima iteración de entrenamiento.
            
                    //std::cout<<std::endl<<"CHECK----2----"<<std::endl;
            EVO();
             //std::cout<<std::endl<<"CHECK----3----"<<std::endl;
            //Evolution routines

                


        }
                  
        
    }

    void Lrn(double TRGERR,int ftI,double GrdLmt=1e4, double s=1.001, double B=0.05255){//Algoritmo de entrenamiento sin evolución
            MXE=1e100;
           // DBG_NND();     
         //while(MXE>TRGERR){
            //std::cout<<"fn: "<< std::setprecision(20)<<GCEF(NEURAL.W)<<std::endl<<std::endl;
            NTRG(ftI,TRGERR,GrdLmt);
            //std::cout<<"fn: "<< std::setprecision(20)<<GCEF(NEURAL.W)<<std::endl<<std::endl;
            
            ME=MXE/PDv.size();
            double cefn;
            //CCHK();
            //Estadisticas y verificación de entrenamiento
            //MXE=GCEF(NEURAL.W);
            ///DBG_NND();
            //std::cout<<"\033[1;33m"<<"MXE: "<< std::setprecision(20)<<MXE<<" \033[0m"<<std::endl<<std::endl;
            //std::cout<<"\033[1;33m"<<"GRN: "<< std::setprecision(20)<<GRN<<" \033[0m"<<std::endl<<std::endl;
            
            SND();
            
    }

    void Prd(int nd){//Updatea los datos para pedicción usando el identificador del vector que contien los datos
       
        LND();//Carga la ultima configuración neuronal disponible
        INN();
        UP(nd);//Carga en las entradas de la red el vector de entrada (nd)
        NEURAL.FRW();//Corre los datos por la red neuronal
        //for (unsigned int i = 0; i < NEURAL.NNOUT.size(); i++) {//Resultados de la predicción
        /* //dbg
        std::cout<<"NEURAL.NNOUT[i]"<<NEURAL.NNOUT[i]<<std::endl;
        //dbg*/
        //  }
    }

///Rutinas de uso simplificadas
        
};
#endif
