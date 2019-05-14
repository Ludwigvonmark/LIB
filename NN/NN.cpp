#include "NN.hpp"

int main (int argc, char* argv[]){
    std::string COMMAND;
    
    std::cout<<"NN V0.25 C++"<<std::endl;

///Manejo de introducción de argumentos
    
    if (argc > 1) {//Existen argumentos

        COMMAND.clear();

        int comands;

        for (comands = 1; comands < argc; ++comands){//Pasa los arguemtnos a la memoria compartida mediante el string INST
  
            COMMAND+=std::string()+argv[comands]+" ";
    
        }    
    }
///Manejo de introducción de argumentos



    NNS NS("GOOG.csv","NND.csv",{1,2,3,4,5,8,9,10,11,12},{1});

    NS.LTD();
    std::reverse(NS.TD.LDATA.begin(),NS.TD.LDATA.end());
    NS.LND();
    NS.INN();
    /*//dbg
    for(int i=0;i<NEURAL.TD.LDATA.size();i++){
        for(int e=0;e<NEURAL.TD.LDATA[i].size();e++){
            std::cout<<NEURAL.TD.LDATA[i][e]<<" ";
        }
        std::cout<<std::endl;
    }
    //dbg*/
//dbg
std::cout<<std::endl;
std::cout<<"Topolog: ";
for(int t=0;t<NS.NEURAL.T.size();t++){std::cout<<NS.NEURAL.T[t]<<" ";}
std::cout<<std::endl;
std::cout<<"Weights: ";
for(int w=0;w<NS.NEURAL.W.size();w++){std::cout<<NS.NEURAL.W[w]<<" ";}
std::cout<<std::endl;
//dbg

NS.LEARN(0.005,5000,10000);

	return 0;
}
