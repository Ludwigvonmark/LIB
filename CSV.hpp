#ifndef CSV_HPP_INCLUDED
#define CSV_HPP_INCLUDED


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


class CSV {
public:

    std::vector<std::vector<double>> DATA;//Data
    std::vector<std::vector<std::string>> ADATA;//Advanced data.
    
    std::fstream OpenData;
    std::ofstream SaveData;
    
    int precc;
        
    std::stringstream ss;//String stream to parse from string
    
    std::string delimiter;
    bool decimdot;

    CSV(int preci=16,std::string delim=",", bool dot=true){
        delimiter=delim;
        decimdot=dot;
        precc=preci;
    }
        
    void SCSV(std::string PATH) {//Guarda DATA en un archivo.

		//SaveData.open(PATH);
            SaveData.open(PATH, std::ofstream::out | std::ofstream::trunc);
		if (SaveData.is_open()) {
			//myfile << "Writing this to a file.\n";
			for (unsigned int i = 0; i< DATA.size(); i++) {

                    
			for (unsigned int e = 0; e< DATA[i].size(); e++) {
   if(e+1>=DATA[i].size()){
                                SaveData <<std::setprecision(precc)<< DATA[i][e];
                            }
                            else{
				SaveData <<std::setprecision(precc)<< DATA[i][e] << delimiter;
                            }
			}

			SaveData << std::endl;
		}
		SaveData.close();
                }
                else{
                    std::cout<<"Error saving CSV"<<std::endl;
                }
	}

    void SACSV(std::string PATH) {//Guarda ADATA en un archivo.

		//SaveData.open(PATH);
            SaveData.open(PATH, std::ofstream::out | std::ofstream::trunc);
		if (SaveData.is_open()) {
			//myfile << "Writing this to a file.\n";
			for (unsigned int i = 0; i< ADATA.size(); i++) {

                    
			for (unsigned int e = 0; e< ADATA[i].size(); e++) {
                            if(e+1>=ADATA[i].size()){
                                SaveData << ADATA[i][e];
                            }
                            else{
				SaveData << ADATA[i][e] << delimiter;
                            }
			}

			SaveData << std::endl;
		}
		SaveData.close();
                }
                else{
                    std::cout<<"Error saving CSV"<<std::endl;
                }
	}

    void LCSV(std::string PATH) {//Carga el archivo
        
            std::vector<double> LINDAT;
            std::vector<std::string> LINADAT;
            double data;
            
                        DATA.clear();
                        ADATA.clear();

		OpenData.open(PATH, std::ios::in);
		if (OpenData.is_open()){
			//std::cout << "Opening Data" << std::endl;
			std::string line = "";

			//read data
                        for(int i=0;!OpenData.eof();i++){
			
				getline(OpenData, line);

				//std::string delimiter = ",";
				size_t pos = 0;
				std::string token;
                                
                                bool lineempty=true;
                                for(int l=0;l<line.size();l++){
                                    if((line[l]!='\n')&&(line[l]!='\r')&&(line[l]!='\0')&&(line[l]!='0')&&(line[l]!='\f')&&(line[l]!='\t')&&(line[l]!=' '))
                                        lineempty=false;
                                }
                                if(lineempty){
                                    line.clear();
                                }
                                else{
                                line+=",";
                                }
                                
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
                                        
					 //LINDAT.push_back(std::stod(token)); 
					       std::istringstream(token)>>data;
                                                LINDAT.push_back(data);
                                                LINADAT.push_back(token);
                                        
					//std::cout << token<<" ";

					line.erase(0, pos + delimiter.length());
				}
				//std::cout <<  std::endl;
				
				if(LINADAT.size()>1){//If exist data
				DATA.push_back(LINDAT);
                                ADATA.push_back(LINADAT);
                                LINDAT.clear();
                                LINADAT.clear();}
				//std::cout << line << std::endl;
			}
			OpenData.close();
		}
		else{
                    std::cout<<"Error loading CSV: "<<PATH<<std::endl;
                }

	}

    void CSVP(std::string sData) { //Parser ofstring with csv like structure
            std::vector<double> LINDAT;
            std::vector<std::string> LINADAT;
            double data;
            
                        DATA.clear();
                        ADATA.clear();
                        
                        std::stringstream ss(sData);

			std::string line = "";

			//read data
                        for(int i=0;!ss.eof();i++){
			
				getline(ss, line);

				//std::string delimiter = ",";
				size_t pos = 0;
				std::string token;
                                
                                bool lineempty=true;
                                for(int l=0;l<line.size();l++){//Si en las lineas solo existe alguno de estos caracteres no las considera
                                    if(line[l]!='\n'&&line[l]!='\r'&&line[l]!='\0'&&line[l]!='0'&&line[l]!='\f'&&line[l]!='\t'&&line[l]!=' '&&line[l]!=',')
                                        lineempty=false;
                                }
                                if(lineempty){
                                    line.clear();
                                }
                                else{
                                line+=",";
                                }
                                
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
                                        
					 //LINDAT.push_back(std::stod(token)); 
					       std::istringstream(token)>>data;
                                                LINDAT.push_back(data);
                                                LINADAT.push_back(token);
                                        
					//std::cout << token<<" ";

					line.erase(0, pos + delimiter.length());
				}
				//std::cout <<  std::endl;
				
				if(LINADAT.size()>1){//If exist data
				DATA.push_back(LINDAT);
                                ADATA.push_back(LINADAT);
                                LINDAT.clear();
                                LINADAT.clear();}
				//std::cout << line << std::endl;

			}


		


	}
    
    void RCD(std::string RECD){//Recovers data and adata from a string
         std::vector<double> LINDAT;
            std::vector<std::string> LINADAT;
            double data;
            
                        DATA.clear();
                        ADATA.clear();
                        
                        std::stringstream ss(RECD);

			std::string line = "";

			//read data
                        for(int i=0;!ss.eof();i++){
			
				getline(ss, line);

				//std::string delimiter = ",";
				size_t pos = 0;
				std::string token;
                                
                                bool lineempty=true;
                                for(int l=0;l<line.size();l++){
                                    if((line[l]!='\n')&&(line[l]!='\r')&&(line[l]!='\0')&&(line[l]!='0')&&(line[l]!='\f')&&(line[l]!='\t')&&(line[l]!=' '))
                                        lineempty=false;
                                }
                                if(lineempty){
                                    line.clear();
                                }
                                else{
                                line+=",";
                                }
                                
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
                                        
					 //LINDAT.push_back(std::stod(token)); 
					       std::istringstream(token)>>data;
                                                LINDAT.push_back(data);
                                                LINADAT.push_back(token);
                                        
					//std::cout << token<<" ";

					line.erase(0, pos + delimiter.length());
				}
				//std::cout <<  std::endl;
				
				if(LINADAT.size()>1){//If exist data
				DATA.push_back(LINDAT);
                                ADATA.push_back(LINADAT);
                                LINDAT.clear();
                                LINADAT.clear();}
				//std::cout << line << std::endl;
			}
			
		

    }
    
    std::string RSTR(){//Puts the data CSV on a string
            std::stringstream ss;
            //std::string str;
            for (int i=0;i<DATA.size();i++){
                for (int e=0;e<DATA[i].size();e++){
                    ss<<DATA[i][e];
                    if(e<DATA[i].size()-1){
                        ss<<',';
                    }
                }
                    
                ss<<'\n';
            }
            return ss.str();
        }
        
    std::string ARSTR(){//Puts the adata CSV on a string
            std::stringstream ss;
            //std::string str;
            for (int i=0;i<ADATA.size();i++){
                for (int e=0;e<ADATA[i].size();e++){
                    ss<<ADATA[i][e];
                    if(e<ADATA[i].size()-1){
                        ss<<',';
                    }
                }
                    
                ss<<'\n';
            }
            return ss.str();
        }
	
};

#endif
