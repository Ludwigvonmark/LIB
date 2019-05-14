#include "EVOL_dbg.hpp"


int main() {
	int debugg;

/*EVOL EVT;

EVT.nNeur=5;
EVT.nLay=3;

EVT.SC();

for(int i=0;i<EVT.SETS.size();i++){
    std::cout<<"SET "<<i+1<<"-> ";
    for(int e=0;e<EVT.SETS[i].size();e++){
        std::cout<<EVT.SETS[i][e]<<" ";
    }
    std::cout<<std::endl;
        std::cout<<std::endl;
}


EVT.TC();

for(int i=0;i<EVT.TSS.size();i++){
    std::cout<<"TOPOLOGIE "<<i+1<<"-> "<<std::endl;
    for(int e=0;e<EVT.TSS[i].size();e++){
        std::cout<<"SET "<<e<<"=>";
         for(int d=0;d<EVT.TSS[i][e].size();d++){
        std::cout<<EVT.TSS[i][e][d]<<" ";}
        std::cout<<std::endl;
    }
    
        std::cout<<std::endl;
}*/




EVOL EVT;
EVT.CT.push_back(1);//Neuronas internas
EVT.CS.push_back(1);//Neuronas internas
EVT.RS();
//EVT.CT.push_back(3);EVT.CT.push_back(1);EVT.CT.push_back(1);

//while(1){
for(int y=0;y<400;y++){
    
   // EVT.GNT();


    
   /* EVT.CT.clear();
    for(int e=0;e<EVT.NT.size();e++)
    EVT.CT.push_back(EVT.NT[e]);*/
    
    //dbg
    
    /*EVT.SSC();
    
    
        EVT.CS=EVT.NS;
    std::cout<<"EVT.NS= ";
    for(int i=0;i<EVT.NS.size();i++){
        std::cout<<EVT.NS[i]<<" ";
    }
    std::cout<<std::endl;
    
    //dbg*/
    
        
    
    EVT.STC();    
    EVT.CT=EVT.NT;
    
    //dbg
    std::cout<<"EVT.TOP= ";
    for(int i=0;i<EVT.CT.size();i++){
        std::cout<<EVT.CT[i]<<" ";
    }
    std::cout<<std::endl;
    
    //dbg
}

	return 0;
}
