#ifndef IPU_HPP_INCLUDED
#define IPU_HPP_INCLUDED
//IP utilities, parser and compositor string <> int.

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

std::vector<int> STR_INTV(std::string IP){//Returns int vector from string
    
}
std::string INTV_STR(std::vector<int> intv){//Returns string from int vector
    if(intv.size()==4){//Correct int ip vector
        std::stringstream stream;
            stream<<intv[0]<<"."<<intv[1]<<"."<<intv[2]<<"."<<intv[3];
            return stream.str();
    }
    else{//Error
        return "";
    }
}

bool ISIP(std::string ip){//Retrun true if the strings contains an ip
    std::string IP=ip;
    
    if(IP.size()<6){//IP has not the minimun size
        return false;
    }
    else if(IP.size()>16){
        return false;
    }
    
    int np=0;
    for(int i=0;i<IP.size();i++){
        if(IP[i]=='.'){
            np++;
        }
    }
    if(np!=3){//If the number of points is not adecuate
        return false;
    }
    return true;//If reaches here the ip must be valid
}

#endif
