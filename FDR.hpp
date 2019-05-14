#ifndef FDR_HPP_INCLUDED
#define FDR_HPP_INCLUDED
//File door. Door for file acces, local or cloud base

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>

#include <algorithm>

#include <iostream> //cout,cin

#include "NET/CLD.hpp"
#include "DAD.hpp"

std::string FDR_SRVIP="";
bool FDR_LOCAL=true;//flag for use DAD-local file door
bool FDR_CLOUD=false;//Flag for cloud based file door

class FDR {    


public:
    DAD LOCAL;
    CDO CLOUD;

    std::string DATA;
    
    void INIT(/*bool cloud=false, bool local=true,std::string ip=""*/){
        //std::cout<<"FDR"<<std::endl;
        DATA.clear();
        
        /*FDR_CLOUD=cloud;
        FDR_LOCAL=local;
        FDR_SRVIP=ip;*/
        
        if(FDR_CLOUD && FDR_LOCAL){//Cloud server, thread blocks here managing server stuff. At client closing conection cloud childs keeps the executuion. 
            std::cout<<"FDR_SRV"<<std::endl;
            CLOUD=CDO(true);
            CLOUD.SERV();
        //Childs keep executing here.
            exit(0); //To make simpler the proces the childs are killed here
        }
        else if(!FDR_CLOUD && FDR_LOCAL){//Local file acces
            std::cout<<"FDR_LOC"<<std::endl;
        }
        else if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()>0){//Cloud client
            std::cout<<"FDR_CLI"<<std::endl;
            CLOUD=CDO(false);
            CLOUD.CCLI(FDR_SRVIP);
            //std::cout<<"FDR Con err: "<<CLOUD.conERR<<std::endl;
            if(!CLOUD.conERR){//Conection estabnlised, server found
               
            }
            else{//Not server found, defaultly swichs to local storage
                FDR_CLOUD=false;
                FDR_LOCAL=true;
                std::cout<<"CDO_SRV NOT FOUND"<<std::endl;
                std::cout<<"FDR_LOC"<<std::endl;
            }
        }
        else if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()==0){//Cloud client whitout direction
            CLOUD=CDO(false);
            CLOUD.CCLI();//Serachs the server and get servIP;
            std::cout<<"FDR_CLI"<<std::endl;
            if(!CLOUD.conERR){//Conection estabnlised, server found
                FDR_SRVIP=CLOUD.SIP;
            }
            else{//Not server found, defaultly swichs to local storage
                FDR_CLOUD=false;
                FDR_LOCAL=true;
                std::cout<<"CDO_SRV NOT FOUND"<<std::endl;
                std::cout<<"FDR_LOC"<<std::endl;
            }
        }
        else{//Behaviour not defined
            std::cout<<"FDR CONFIG ERROR"<<std::endl;
        }
    }
    
    FDR(/*bool cloud=false, bool local=true,std::string ip=""*/){//Local storage, server or simple configs.
        
       INIT(/*cloud,local,ip*/);
    }

    
    
        //Simple functions
   void SF(std::string PATH, std::string data) {//Saves data.
       if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()>0){//Cloud client save data
            CLOUD.CCLI(FDR_SRVIP);//Creates the conection
            DATA=data;
            CLOUD.SENDD=DATA;
            CLOUD.SD(PATH);//Saves CLOUD.SENDD on path on the server side
            CLOUD.CL();//Closes the conection
       }
       else if(!FDR_CLOUD && FDR_LOCAL){//Local data save
           if(LOCAL.SF(PATH,data)){//Data saved correctly
            }
            else{//Data save error.
            }
        }
        else{//Configuration error
            std::cout<<"FDR CONFIG ERROR"<<std::endl;
        }
    }

    void LF(std::string PATH) {//Load data.
       if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()>0){//Cloud client save data
            CLOUD.CCLI(FDR_SRVIP);//Creates the conection
            CLOUD.LD(PATH);//Saves CLOUD.SENDD on path on the server side
            DATA=CLOUD.RECVD;
            CLOUD.CL();//Closes the conection
            
       }
       else if(!FDR_CLOUD && FDR_LOCAL){//Local data save
           DATA=LOCAL.RLF(PATH);
        }
        else{//Configuration error
            std::cout<<"FDR CONFIG ERROR"<<std::endl;
        }
    }
    
    void PH(std::string PATH){//Get file structure on the current folder
       if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()>0){//Cloud client save data
            CLOUD.CCLI(FDR_SRVIP);//Creates the conection
            CLOUD.PH(PATH);//Saves CLOUD.SENDD on path on the server side
            DATA=CLOUD.RECVD;
            CLOUD.CL();//Closes th
       }
       else if(!FDR_CLOUD && FDR_LOCAL){//Local data save
            DATA=LOCAL.RPH(PATH);
        }
        else{//Configuration error
            std::cout<<"FDR CONFIG ERROR"<<std::endl;
        }
    }


    void DL(std::string PATH){//delete the file with the current path
       if(FDR_CLOUD && !FDR_LOCAL && FDR_SRVIP.size()>0){//Cloud client save data
            CLOUD.CCLI(FDR_SRVIP);//Creates the conection
            CLOUD.DL(PATH);//Saves CLOUD.SENDD on path on the server side
            CLOUD.CL();//Closes th
       }
       else if(!FDR_CLOUD && FDR_LOCAL){//Local data save
           if(LOCAL.DF(PATH)){//Delete correctly
               
            }
            else{//Data save error.
                
            }
        }
        else{//Configuration error
            std::cout<<"FDR CONFIG ERROR"<<std::endl;
        }
    }
};

#endif
