#ifndef DBGU_HPP_INCLUDED
#define DBGU_HPP_INCLUDED
//Debug utilities.

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

void DBG_STD(const std::vector<std::vector<std::string>> &string2Dvect, std::string title="DBG 2DV", bool enab=true){
    if(enab){
    std::cout<<title<<std::endl;
            for (int i=0; i<string2Dvect.size();i++){
                for (int q=0;q<string2Dvect[i].size();q++){
                    std::cout<<string2Dvect[i][q]<<"\t";
                }
                std::cout<<std::endl;
            }
    }
}

void DBG_STD(const std::vector<std::string> &string1Dvect, std::string title="DBG 2DV", bool enab=true){
    if(enab){
    std::cout<<title<<std::endl;
            for (int i=0; i<string1Dvect.size();i++){
                    std::cout<<string1Dvect[i]<<"\t";
                }
                std::cout<<std::endl;
            }
}

void DBG_STD(const std::vector<std::vector<double>> &string2Dvect, std::string title="DBG 2DV", bool enab=true){
    if(enab){
    std::cout<<title<<std::endl;
            for (int i=0; i<string2Dvect.size();i++){
                for (int q=0;q<string2Dvect[i].size();q++){
                    std::cout<<string2Dvect[i][q]<<"\t";
                }
                std::cout<<std::endl;
            }
    }
}

void DBG_STD(const std::vector<double> &string1Dvect, std::string title="DBG 2DV", bool enab=true){
    if(enab){
    std::cout<<title<<std::endl;
            for (int i=0; i<string1Dvect.size();i++){
                    std::cout<<string1Dvect[i]<<"\t";
                }
                std::cout<<std::endl;
            }
}

void DBG_STD(const std::vector<long> &string1Dvect, std::string title="DBG 2DV", bool enab=true){
    if(enab){
    std::cout<<title<<std::endl;
            for (int i=0; i<string1Dvect.size();i++){
                    std::cout<<string1Dvect[i]<<"\t";
                }
                std::cout<<std::endl;
            }
}

#endif
