#include "NN.hpp"
#include "../CSV.hpp"
#include "../LINUX/SML.h"



int main() {
  
    
std::vector<std::vector<double>>TD;
std::vector<std::vector<double>>RD;

std::cout<<"NN_dbg"<<std::endl;
  

SMLL NNSM;
NNSM.AXSMZd=10000000;
NNSM=SMLL(100,2000);  



CSV TRD;
CSV NPD;//Neural predictión data, resultados de prediccion
TRD.LCSV("SF_TST.csv");
//CSV ND("XOR_TST_NND.csv");

for(int l=0;l<TRD.DATA.size();l++){
    TD.push_back({TRD.DATA[l][0],TRD.DATA[l][1]});
    //TD.push_back(TRD.DATA[l][1]);
    RD.push_back({TRD.DATA[l][2]});
    for( int c=0; c<TRD.DATA[l].size();c++){
        std::cout<<TRD.DATA[l][c]<<" ";
    }
    std::cout<<std::endl;
}
    std::cout<<std::endl;


NNS NEURAL(TD,RD);//Mete a la red los vectores de datos y redultados a entrenar
NEURAL.INN();

for(int c=0;c<NEURAL.NEURAL.T.size();c++){
        std::cout<<NEURAL.NEURAL.T[c]<<" ";
    }
    std::cout<<std::endl;

for(int c=0;c<NEURAL.NEURAL.W.size();c++){
        std::cout<<NEURAL.NEURAL.W[c]<<" ";
    }
    std::cout<<std::endl<<std::endl;
    
    //Fase de entrenamiento

NEURAL.LrnEv(0.5,100000,10000,1e2,2,0.051);


    
        std::cout<<"TRD--"<<std::endl;
        
        
        for(int l=0;l<TRD.DATA.size();l++){
    for( int c=0; c<TRD.DATA[l].size();c++){
        std::cout<<TRD.DATA[l][c]<<" ";
    }
    std::cout<<std::endl;
}
    std::cout<<std::endl;
        
        
                std::cout<<"NS--"<<std::endl;
        
for(int c=0;c<NEURAL.NEURAL.T.size();c++){
        std::cout<<NEURAL.NEURAL.T[c]<<" ";
    }
    std::cout<<std::endl;

for(int c=0;c<NEURAL.NEURAL.W.size();c++){
        std::cout<<NEURAL.NEURAL.W[c]<<" ";
    }
    std::cout<<std::endl<<std::endl;
    
    //Fase de entrenamiento
    
    
        std::cout<<"NO--"<<std::endl;
        
            NPD.DATA.clear();            

   
for (int sds=0;sds<CLo.Pr.size();sds++){    
    
    NEURAL.UP(sds);
    //NEURAL.UP(2);
    NEURAL.Prd(sds);
    

    std::vector<double> RPd(NEURAL.NEURAL.NNOUT.begin(), NEURAL.NEURAL.NNOUT.end());
    NPD.DATA.push_back(RPd);
    
    
    //Cuadratic error function
    
    //Cuadratic error function
    
    std::cout<<std::endl;
    
for(int c=0;c<NEURAL.NEURAL.D.size();c++){
    std::cout<<NEURAL.NEURAL.D[c]<<" ";
}
std::cout<<"--"<<std::endl;
std::cout<<std::endl;

}
    //Fase de entrenamiento
    NNSM.W(NPD.RSTR());
        std::cout<<"NNSM: "<<NPD.RSTR();
    //Guardado de datos
    NEURAL.SC.SCSV("DBG_NN.csv");
    
    //SM DBG
    NNSM.R();
    std::cout<<"NNSM: "<<NNSM.AXSM;
    CSV fnD;
      fnD.RCD(NNSM.AXSM);
      for(int e=0;fnD.DATA.size()>e;e++){
          for (int c=0;fnD.DATA[e].size()>c;c++){
              std::cout<<e<<" "<<c<<" e,c "<<fnD.DATA[e][c]<<" ";
        }
        std::cout<<std::endl;
    }
    //SM DBG
    
    //Guardado de datos
    

	return 0;
}
