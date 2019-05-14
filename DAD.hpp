#ifndef DAD_HPP_INCLUDED
#define DAD_HPP_INCLUDED
//Data adquisitor and depositor

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

#define GCC_VERSION (__cplusplus)
#if GCC_VERSION >201700 //201703L
#include <experimental/filesystem>
#endif

class DAD {    
    std::fstream OpenData;
    std::ofstream SaveData;
    
    std::string DATA;
    
    public:
    DAD(){
    }
        
        //Simple functions
    bool SF(std::string PATH) {//Saves data on file.
        SaveData.open(PATH, std::ofstream::out | std::ofstream::trunc);
            if (SaveData.is_open()) {
                SaveData << DATA;
                SaveData.close();
                //std::cout<<"DAD_SF_CORRECT"<<std::endl;
                return true;
            }
            else{
                SaveData.close();
                std::cout<<"DAD_SF_ERROR"<<std::endl;
                return false;
            }
	}

    bool SF(std::string PATH,std::string data) {//Saves data on file.
        DATA=data;
        return SF(PATH);
	}

    bool LF(std::string PATH) {//Loads data from file el archivo
        OpenData.open(PATH, std::ios::in); 
        if (OpenData.is_open()){
                std::stringstream stream;
                stream<<OpenData.rdbuf();
                //std::cout << "Opening Data" << std::endl;
                OpenData.close();
                DATA=stream.str();
                return true;

            }
            else{
                    //std::cout<<"Error loading file: "<<PATH<<std::endl;
                OpenData.close();
                DATA.clear();
                return false;
            }
	}
	
    std::string RLF(std::string PATH) {//Loads data from file el archivo
        bool succ=LF(PATH);
        if(succ)
            return DATA;
        else 
            return "";
	}
        //Simple functions
        
        //Experimental filesistem
        
    bool PH(std::string PATH){//Gets file structure inside path csv like structure    
        bool succ=false;
         #if GCC_VERSION >201700 //201703L
            succ=true;
            std::stringstream stream;
            for (auto & p : std::experimental::filesystem::directory_iterator(PATH)){//itera por todos los archivos en la carpeta de las NC
                std::string CFILE= p.path();
                stream<<CFILE<<",\n";
            }
            DATA=stream.str();
        #endif
            return succ;    
    }
    
    std::string RPH(std::string PATH){//Return file structure
        if(PH(PATH)){
            return DATA;
        }
        else{
            return "";
        }
    }
///Comon functions
   bool DF(std::string PATH){//Deletes file data
        int n=0; 
        #if GCC_VERSION >201700 //201703
            n = std::experimental::filesystem::remove(PATH);
        #endif
        if(n<=0){//Error deleting, file non existent
            return false;
        }
        else{
            return true;
        }
    }
    
    //Experimental filesistem
};

#endif
