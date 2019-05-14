#ifndef CLD_HPP_INCLUDED
#define CLD_HPP_INCLUDED


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
#include "LINUX/NET.h"
#include "IPU.hpp"
#include "../LINUX/MPR.hpp"
#include "../DAD.hpp"
#include "../DBGU.hpp"

    //Split with token function pack
    #ifndef SPLIT
    #define SPLIT
    template<typename Out>
    void split(const std::string &s, char delim, Out result) {
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) {
            *(result++) = item;
        }
    }
    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> elems;
        split(s, delim, std::back_inserter(elems));
        return elems;
    }
    #endif
    //Split with token function pack

class CDO {//Cloud data object, saves and load data from-to cloud if client and does it localy if server. Server also keep information on conected devices and statistics about them.
    
public:

    int errorT=0;//0 no error, 1 conection error, 2 non existen file
    bool conERR=false;
    
    bool server=true;//True object acts like server, false acts like client.
    bool SREX=true;//Served loop execution
    NET *DATAPIPE;
    
    std::string RECVD;//Last data recived
    std::string SENDD;//Last data sended or to send
    
    std::string RECVI;//Last instruction recived
    std::string SENDI;//Last instruction sended or to send
    
    //Operation tickets
    std::string KEY="3e&h+";//Key for identification
    
    char token='#';
    char error='%';
    
    std::string OP="~&";//"LD" save, load operation
    //Operation tickets

    
    //Server variables
    std::string cIP;//current client ip
    std::vector<std::string> hIPs;//List of historic of ips conected
    MPR MPSS;//Multi process server structure.
    std::fstream OpenData;
    std::ofstream SaveData;
    //Server variables
    
    //Client variables
    std::string SIP;//Server ip
    std::vector<std::vector<int>>IPit;//IP iterator
    //Client variables
    
    //Local data handler
    DAD LDH;
    //Local data handler

    CDO(){}
    
    CDO(bool srv){
        if (srv){
            
            DATAPIPE=new NET(TCP_SRV,"3990");
            server=true;
            
        }
        else{
            DATAPIPE=new NET(TCP_CLT,"3990");
            server=false;
            
        }
    }

    void SD(std::string PATH) {//Saves data to cloud.
        
        if(server){//Server function
            if(LDH.SF(PATH,RECVD)){
                SENDD=token;
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
            else{
                std::cout<<"Error saving DATA"<<std::endl;
                SENDD=error;
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
        }
        else{//Client function
            SENDI="SD";
            DATAPIPE->TCP_CLT_SND(SENDI+token+PATH+"\n"+SENDD);
            DATAPIPE->TCP_CLT_RCV();
            RECVD=DATAPIPE->DR;
        }
    }

    void LD(std::string PATH) {//Load data from cloud.
        
        if(server){//Server function
            
            SENDD=LDH.RLF(PATH);
            if(SENDD.size()>0){
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
            else{
                //std::cout<<"Error loading file: "<<PATH<<std::endl;
                SENDD=error;
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
            
        }
        else{//Client funtion
            SENDI="LD";
            DATAPIPE->TCP_CLT_SND(SENDI+token+PATH+"\n");
            DATAPIPE->TCP_CLT_RCV();
            RECVD=DATAPIPE->DR;
        }
        
    }
    
    void PH(std::string PATH){//Get file structure on the curremt folder
        if(server){//Server function
            
            SENDD=LDH.RPH(PATH);
            if(SENDD.size()>0){
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
            else{
                //std::cout<<"Error loading file: "<<PATH<<std::endl;
                SENDD=error;
                DATAPIPE->TCP_SRV_SND(SENDD);
            }
                              
        }
        else{
            SENDI="PH";
            DATAPIPE->TCP_CLT_SND(SENDI+token+PATH+"\n");
            DATAPIPE->TCP_CLT_RCV();
            RECVD=DATAPIPE->DR;
        }
    }


    void DL(std::string PATH){//delete the file on the current path
        if(server){//Server function
            if(LDH.DF(PATH)){
                SENDD=token;
            }
            else{
                SENDD=error;
            }
            DATAPIPE->TCP_SRV_SND(SENDD);
        }
        else{
            SENDI="DL";
            DATAPIPE->TCP_CLT_SND(SENDI+token+PATH+"\n");
            DATAPIPE->TCP_CLT_RCV();
            RECVD=DATAPIPE->DR;
        }
    }
    
    void CL(){//close the conection
        if(server){//Server function
        }
        else{
            SENDI="CL";
            DATAPIPE->TCP_CLT_SND(SENDI+token+"\n");
        }
    }

            std::vector<std::string> CLDInP(std::string recvi){//Cloud data instruction parser, extracts the op, and op specific.
        std::string INStr=recvi;
        return split(recvi, token);
    }
    
    void SERVR_EX(){//Server execution, blocks the current thread
        bool CH_EX=true;
        DATAPIPE->TCP_SRV_SND(KEY);//Server sends KEY
        while(CH_EX){
        DATAPIPE->TCP_SRV_RCV();//Server lisents to get instruction
        cIP=std::string(DATAPIPE->s);//Gets the ip
        
        RECVI.clear();
        std::stringstream inststream(DATAPIPE->DR);
        std::getline(inststream,RECVI);
        
        RECVD.clear();
        RECVD=DATAPIPE->DR;
        RECVD.erase(0, RECVD.find("\n") + 1);
        
        //std::cout<<"RECVI: "<<RECVI<<std::endl;
        //std::cout<<"RECVD: "<<RECVD<<std::endl;
        
        std::vector<std::string> INst=split(RECVI, token);
        //DBG_STD(INst,"INSTRUCS PARS:",true);
        
        
        if(INst.size()>1){//If the client petition contains path
            std::string path=INst[1];
        
            if(INst[0]=="SD"){//Server save data op
                SD(path);
            }
            else if(INst[0]=="LD"){//Server load data op
                LD(path);
                
            }
            else if(INst[0]=="DL"){//Path content op
                DL(path);
            }
            else if(INst[0]=="PH"){//Path content op
                PH(path);
            }
            
        }
        
        if(INst[0]=="CL"){//Close connection
                //std::cout<<"Closed conection"<<std::endl;
            DATAPIPE->TCP_SRV_CLS();
            CH_EX=false;
            }
        else{
            
        }
        }
    } 
    
    void SERV(){//Create server, mutithreats the incoming conections
        //std::cout<<"CDO SERV"<<std::endl;
        if(server){
            //std::cout<<"CDO SERV.1"<<std::endl;
            //std::cout<<"CDO SERV.1.2"<<std::endl;
            MPSS=MPR();
            //std::cout<<"CDO SERV.1.3"<<std::endl;
            while(SREX){
            DATAPIPE->TCP_SRV_LS();//Blocks the tread
            MPSS.CRCH();
            if(MPSS.PRN()==-1){//Mater threat
                DATAPIPE->TCP_SRV_CLS();//Closes the conection, that the children takes care of and reestart the lisening
            }
            else{//Clild takes care of the conection
                SREX=false;//Asures proces to exit after finishing service.
                SERVR_EX();//Execute the instruction ask for the client.
            }
            
            }
        }
    }

    bool CLCON_LOC(){//return true if server on local host
        SIP=INTV_STR({127,0,0,1});//Check local host
            DATAPIPE->TCP_CLT_CN(SIP);        
            if(DATAPIPE->CON_ERR){//SERVER INEXISTENT ON DIRECTION
                return false;
            }
            else{
                DATAPIPE->TCP_CLT_RCV();//Gets the key
                RECVD=DATAPIPE->DR;//RECVD contains key
                return true;
            }
    }
    
    bool CLCON_LNE(){//return true if server on local network
        for(int e=0;e<255;e++){//Local iterator
            SIP=INTV_STR({192,168,1,e});
            //std::cout<<"SEARCH COD_SRV: "<<SIP<<std::endl;
            DATAPIPE->TCP_CLT_CN(SIP);        
            if(DATAPIPE->CON_ERR){//SERVER INEXISTENT ON DIRECTION
            }
            else{
                DATAPIPE->TCP_CLT_RCV();//Gets the key
                RECVD=DATAPIPE->DR;//RECVD contains key
                return true;
                //break;
            }
        }
        return false;
    }
    bool CLCON_EXT(){//return true if server on MASMOVIL web net
        for(int e=30;e<51;e++){//EXTERNAL iterator
            for(int y=0;y<255;y++){
                SIP=INTV_STR({78,30,e,y});
                //std::cout<<"SEARCH COD_SRV: "<<SIP<<std::endl;
                DATAPIPE->TCP_CLT_CN(SIP);        
                        if(DATAPIPE->CON_ERR){//SERVER INEXISTENT ON DIRECTION
                        }
                        else{//Server found
                            DATAPIPE->TCP_CLT_RCV();//Gets the key
                            RECVD=DATAPIPE->DR;//RECVD contains key
                            return true;
                        }
                    }

                }
                return false;
    }
    
    void CCLI(){//Creates client with brute force ip search
        conERR=false;
        server=false;
        std::cout<<"SEARCHING COD_SRV"<<std::endl;
        if(CLCON_LOC()){//Conection establised on local host
            
        }
        else{//Non existent server on local host
            if(CLCON_LNE()){//Server existent on local network
                
            }
            else{//Non exixten server on local network
                if(CLCON_EXT()){//Server exitent on MASMOVIL net
                }
                else{//Not avaliable server
                    conERR=true;
                }
            }
        }
    }
    
    void CCLI(std::string serverIP){//Creates client
        server=false;
        DATAPIPE->TCP_CLT_CN(serverIP);
        conERR=DATAPIPE->CON_ERR;
        //std::cout<<"CLO conERR: "<<conERR<<std::endl;
        if(!conERR){//If the conexion is sucssesful gets the key
        DATAPIPE->TCP_CLT_RCV();//Gets the key
        RECVD=DATAPIPE->DR;//RECVD contains key
        }
        
    }
    


    
    bool SCH(){//Client server checker, true if server responds with key.
        
    }
    
    
	
};

class CPO{//Cloud process object, , give and recive proces data related from-to. Server also keep information on conected devices and statistics about them.
    
};

class CLSTR{//Clouster class group of CPOs and CDOs
    
};


#endif
