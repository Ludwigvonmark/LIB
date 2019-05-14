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
    int precc;
    std::stringstream ss;//String stream to parse from string
    std::string delimiter;
    bool decimdot;

    CSV(int preci=16,std::string delim=",", bool dot=true){
        delimiter=delim;
        decimdot=dot;
        precc=preci;
    }
    CSV(const CSV& cs){
        DATA=cs.DATA;
        ADATA=cs.ADATA;
        precc=cs.precc;
        //ss=cs.ss;
        delimiter=cs.delimiter;
        decimdot=cs.decimdot;
    }
    CSV& operator=(const CSV& cs) { //A=B
        DATA=cs.DATA;
        ADATA=cs.ADATA;
        precc=cs.precc;
        //ss=cs.ss;
        delimiter=cs.delimiter;
        decimdot=cs.decimdot;
    };
    
    void DEC(std::string RECD){//Decoder, recovers data and adata from a string
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
                                LINADAT.clear();
                    
                }
				//std::cout << line << std::endl;
			}
			
		

    }
    
    std::string ENC(){//Double floating point encoder, puts the data CSV on a string
            std::stringstream ss;
            //std::string str;
            for (int i=0;i<DATA.size();i++){
                for (int e=0;e<DATA[i].size();e++){
                    ss<<std::setprecision(precc)<<DATA[i][e];
                    if(e<DATA[i].size()-1){
                        ss<<',';
                    }
                }
                    
                ss<<'\n';
            }
            return ss.str();
        }
        
    std::string AENC(){//String encoder, puts the adata CSV on a string
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
