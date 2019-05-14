#ifndef EV_H_INCLUDED
#define EV_H_INCLUDED
//Evolution routines

class EVOL{
public:
    std::vector <int> SET;
    std::vector<std::vector<int>> SETS;
    
    long ITER=0;
    
    int nNeur=0;
    int nLay=0;
        
    std::vector<int> T;
    std::vector<std::vector<int>> TS;
    std::vector<std::vector<std::vector<int>>> TSS;
    
    std::vector<int> CS; //Current set
    std::vector<int> NS; //New set
    std::vector<int> CT; //Current topologie
    std::vector<int> NT; //New topoligie
    int fc=0;
    int fn=0;
    int swc=1;
    int swn=1;
    
    bool nT=true;//Se ha creado una topologia nueva
    bool nS=true;//Se ha creado un set nuevo
    
    EVOL(){}
    
    /*EVOL(int sIter){
        
    }*/
    
    /*~EVOL(){
        T.clear();
        
        SET.clear();
        SETS.clear();
    }*/

bool VCI(std::vector<int> vc){
                bool vci=true;
        for(int v=1;v<vc.size();v++){
            if(vc[v-1]==vc[v]){vci=true;}
            else {vci=false; break;}
        }
        return vci;
    }

    
    bool CvS(){//Comprueba la validez del set
        bool cvs=true;
        for(int v=1;v<SET.size();v++){
            if(SET[v-1]>=SET[v]){cvs=true;}
            else {cvs=false; break;}
        }
        return cvs;
    }
    
    bool CvSS(){//Comprueba la validez del set secuencial
        bool cvs=true;
        for(int v=1;v<NS.size();v++){
            if(NS[v-1]>=NS[v]){cvs=true;}
            else {cvs=false; break;}
        }
        return cvs;
    }
    
    void SC(){//Creación de los sets, creación distintos dominios a combinar a partir del numero de neuronas y el numero de capas. 
        //Secure check
        if(nLay>nNeur){
            std::cout<<"Error, EVOL.CS, bad config"<<std::endl;
        }
        else{
        
        bool ittt=true;//Existen más sets
        
        //Inicializacuión del primer set.
        
        SET.clear();
                
        SET.push_back((nNeur-nLay)+1);
        for(int un=1;un<nLay;un++){ SET.push_back(1);}
        
        SETS.push_back(SET);
        
        //Inicializacuión del primer set.
        
        
        //Inicialización de sets sucesivos.

        while(ittt){
        
            
            for(int it=0;it<(nLay-1);it++){//Recorre todas las capas excepto la última
            
                /*//dbg
                std::cout<<"it="<<it<<std::endl;
                //dbg*/
            
                for (int sit=(it+1);sit<nLay;sit++){//Recorre todas las capas desde i+1 hasta la última
            
                    /*//dbg
                    std::cout<<"sit="<<sit<<std::endl;
                    //dbg*/
                
                
                    while(SET[it]>(SET[sit]+1)){
                        SET[sit]+=1;
                        SET[it]-=1;
                        
                            /*//dbg
                            for(int e=0;e<SET.size();e++){
                                std::cout<<SET[e]<<" ";
                            }
                            std::cout<<std::endl;
                            std::cout<<std::endl;
                            //dbg*/
                        
                        SETS.push_back(SET);
                    }
            
                }
            }
             
             /*//dbg
                    std::cout<<"CvS"<<CvS()<<std::endl;
                   // dbg*/
            
            if(!CvS()){
                std::sort(SET.begin(),SET.end(), std::greater<int>());
                         
                                   /*//dbg
                           for(int e=0;e<SET.size();e++){
                               std::cout<<SET[e]<<" ";
                           }
                          std::cout<<std::endl;
                          std::cout<<std::endl;
                            //dbg*/
                
              
            }
            else{ittt=false;}

       
    }
    
    //Inicialización de sets sucesivos.
           
    }
        
    }
    
    void RS(){//Recupera el set actual apartir de la topologia actual
        CS.clear();
        
        CS=CT;
        std::sort(CS.begin(),CS.end(), std::greater<int>());
        
        nLay=CT.size();
        
        nNeur=0;
        for(int l=0;l<nLay;l++){
            nNeur+=CT[l];
        }
        
        
    }
    
    bool SSC(){//Secuencial set creator; Call when SST need new set only
        NS=CS;
        bool ittt=true;//Existen más sets
        
        //dbg
        //std::cout<<"SSC_INIT OK"<<std::endl;
        //dbg

        if(NS.size()<=1){
                ittt=false;
                //dbg
                //std::cout<<"SSC_LOWSZ OK"<<std::endl;
                //dbg
        }
        
        if(ittt){
        
            
                for(int it=0;it<(nLay-1);it++){//Recorre todas las capas excepto la última
            
                    //dbg
                    //std::cout<<"it="<<it<<std::endl;
                    //dbg
            
                    for (int sit=(it+1);sit<nLay;sit++){//Recorre todas las capas desde i+1 hasta la última
            
                        //dbg
                        //std::cout<<"sit="<<sit<<std::endl;
                        //dbg
                
                
                        if(NS[it]>(NS[sit]+1)){
                            NS[sit]+=1;
                            NS[it]-=1;
                            
                            //dbg
                            //std::cout<<"NS= ";
                            //for(int i=0;i<NS.size();i++){
                            //    std::cout<<NS[i]<<" ";
                            //}
                            //std::cout<<std::endl;
                            
                            
                            return true;                            

                        }
                        else{ittt=false;}
            
                    }
                }
             
                /*//dbg
                std::cout<<"CvS"<<CvS()<<std::endl;
                // dbg*/
            
                if(!CvSS()){
                    std::sort(NS.begin(),NS.end(), std::greater<int>());
                }
                else if(!CvSS()){ittt=false;} 
        }
            
            
        if(nLay==nNeur){
                nLay=1;
                nNeur++;  
                    
                NS.clear();
                
                NS.push_back((nNeur-nLay)+1);
                for(int un=1;un<nLay;un++){ NS.push_back(1);}                   
        }
        else if(!ittt) {
                nLay++;
                NS.clear();                
                NS.push_back((nNeur-nLay)+1);
                for(int un=1;un<nLay;un++){ NS.push_back(1);}
                //dbg        
                //std::cout<<"SSC_ADDLY OK"<<std::endl;
                //dbg
        }
        
        return true;
        
            
    }
        
       
        
    void TC(){//Crea las topologias a partir de los sets
        T.clear();
        TS.clear();
        TSS.clear();
        
        int sw=1;
        //T.assign(SETS[0].size(),0);
        
        //Combinador
        for(int ts=0;ts<SETS.size();ts++){//Itera entre los diferentes sets               
        
            for(int f=0;f<factorial(SETS[ts].size());f++){//Itera entre todas las combinaciones posibles considerando todos los elementos diferentes       
            
            if((f>1)&&(TS[0]==SETS[ts])&&(sw==1)){break;}
            
            
                if(SETS[ts][0]!=SETS[ts][sw]){
                
                    
                
                    if(!((f>1)&&(TS[0]==SETS[ts]))){ 
                        
                    TS.push_back(SETS[ts]);
                
                    }
                
                }
               
                std::swap(SETS[ts][0],SETS[ts][sw]); 
            
                sw++;
                if(sw>=SETS[ts].size()){sw=1;}
                
            }
             
            if(!TS.empty()){
                
                TSS.push_back(TS);
                TS.clear();
            
                /*//dbg
                for(int i=0;i<TSS.size();i++){
                    std::cout<<"TOPOLOGIE "<<i+1<<"-> "<<std::endl;
                    for(int e=0;e<TSS[i].size();e++){
                        std::cout<<"SET "<<e<<"=>";
                        for(int d=0;d<TSS[i][e].size();d++){
                            std::cout<<TSS[i][e][d]<<" ";}
                            std::cout<<std::endl;
                    }
                    
                    std::cout<<std::endl;
                }
                //dbg*/                
            }
                
            //Nuevo vector de topologias
                       
        }
        
/*        TS.clear();
        
        for (int e=0;e<TSS.size();e++){
            for (int i=0;i<TSS[e].size();e++){
                TS.push_back(TSS[e][i]);
            }
            
       }*/
        
        //Combinador
    }
    
    bool FI(std::vector<std::vector<int>> Bi, std::vector<int>Un){//Encuentra igualdades entre un vector bidimensional y uno unidimensional
            for(int i=0;i<Bi.size();i++){
                    if(Bi[i]==Un){
                            return true;
                }
        }
            return false;
}
        
   bool STC(){//Crea las topologias secuencialmente a partir del set actual o el nuevo si es requerido
 std::vector<std::vector<int>> tT;
        
        RS();
        
        NT.clear();
        NT=CS;
        
                if(NT.size()==1){
              
                SSC();//Crea un set nuevo                
                NT=NS; 
                
                return true;
        }
        
        swc=1;
                
        
        while(NT!=CT){
                
                //dbg
                //std::cout<<"NT!=CT OK"<<std::endl;
                //dbg
                
        std::swap(NT[0],NT[swc]); 
                swc++;
                if(swc>=CS.size()){swc=1;}
                
                tT.push_back(NT);
        }


        while((NT==CT)||(NT==CS)||FI(tT,NT)){

                //dbg
                //std::cout<<"NT==CT OK"<<std::endl;
                //dbg
                        
               // if(NT[0]!=NT[swc]){
                        std::swap(NT[0],NT[swc]); 
                //}
                swc++;
                if(swc>=CS.size()){swc=1;}
                
                if((NT==CS)&&(swc==1)){
                        SSC();//Crea un set nuevo                
                        NT=NS;             
                        return true;
                }
        }
        

        
        return true;
        
        
           
}


    void GNT(std::vector<int> cT){//Genera una nueva topologia para la red
       CT.clear();
       for(int ctt=1;ctt<cT.size()-1;ctt++){
               CT.push_back(cT[ctt]);
}
        STC();
        /*while(!STC()){
                   
           // while(!SSC()){
                        
           // }
        }*/
        
        }

       
  
    
};


#endif
