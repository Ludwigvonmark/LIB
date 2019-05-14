#ifndef MPR_HPP_INCLUDED
#define MPR_HPP_INCLUDED
//Multi proces

#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <sys/wait.h>


class MPR {//Multiproces lib

    int nPr=1;//Fork number of subproceses; 1 is necesary because the master treat keeps block until treat finish, in this case treat 0 is the proces how makes the work. 
    int PrN=0;//Proces number, used as work distributor number the childrens from 0 to n
    int status;
    std::vector<pid_t> pid;//Pid for fork;
    
    public:
        
    std::vector <int> CHLDEX;//Vector with the exit code of the thread on the same order as PrN
        
    MPR(){
        
    }
    
    void CRCH(){//Create child
        signal(SIGCHLD, SIG_IGN);//Prevent zombie creation
        pid.push_back(fork());
        if(pid[pid.size()-1]==0){//slave                
                PrN++;
            }
        else if(pid[pid.size()-1]>0){//Master
                PrN=-1;//Sets de master initial proces number to a negative value, so it dont do work
                //Wait for proceses to finish

            }
    }
    
    void WFCH(){//Master waits for childrens here until end of execution.
        if(PrN==-1){
            for(int i=0;i<nPr;i++){
            waitpid(pid[i], &status, WUNTRACED);
            CHLDEX.push_back(status);
            }
            pid.clear();
        }
        
    }
    
   
    void CSPS(int NpR=1){//Creates subproces structure, master proces waits here
        nPr=NpR;
        pid.clear();
        for(int i=0;i<nPr;i++){
            PrN=i;
            pid.push_back(fork());
            if(pid[i]==0){//slave                
                break;
            }
            else if(pid[i]>0){//Master
                PrN=-1;//Sets de master initial proces number to a negative value, so it dont do work
                //Wait for proceses to finish
                
            }
            else{
                std::cout<<"FORK ERROR"<<std::endl; 
            }
        }
        if(pid[0]>0){//Waiting routine for the master proces
            CHLDEX.clear();
            std::cout<<"Master wait"<<std::endl; 
            for(int i=0;i<nPr;i++){
                waitpid(pid[i], &status, WUNTRACED);
                CHLDEX.push_back(status);
            }
            
        }
    }
    
    
    
    int PRN(){//Retrurn the treat id, -1 for master. 
        return PrN;
    }

};

#endif
