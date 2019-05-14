#ifndef DPR_H_
#define DPR_H_
//Clock and date utilities: parser and modifier
//Cronometer
//For linux sistems
//Valid until 2038

#include <stdio.h>
#include <iostream>   
#include <string.h>
#include <sys/time.h> 
#include <time.h>

class DATE{
private:
    time_t dateT;
    std::string dateS;
    long epoch;
    struct tm tm;
    
    time_t rawtime;
  struct tm *tminfo;
  
public:
    bool errr=true;
    void GT(){//Puts time object to current date
        time(&dateT);
        
time ( &rawtime );
  tminfo = localtime ( &rawtime );
        
    }
    void ST(int epc){
        dateT = static_cast<time_t>(epc);
    }
    
    
    void ST(std::string time){//Sets current object time
        //strptime(str.c_str(), "%Y-%m-%d %T", &tm);
        if(strptime(time.c_str(), "%Y-%m-%d %H:%M:&S", &tm)==NULL){
            //std::cout<<"Wrong format time string"<<std::endl;
            errr=true;
        }
        //dateT=timegm(&tm);
        dateT=0;
        dateT=mktime(&tm);
        if(dateT==-1){
            //std::cout<<"Error creating time_t"<<std::endl;
            errr=true;
        }
        else{errr=false;}
    }
    
   std::string RTS(){//Return time to string
        dateS=ctime(&dateT);
       return dateS;
    }
    
    long RTE(){//Return epoch
        epoch=(long)dateT;
        return epoch;
    }
    
    void AdT(){//Adds time to current loaded date
        
    }
    
    void SuT(int day=0){//Substracts n days time to current loaded date
        
        for(int n=0;n<day;n++){
            if(tminfo->tm_mday==1){
                if(tminfo->tm_mon==0){
                    tminfo->tm_year-=1;
                    tminfo->tm_mon=11;
                    tminfo->tm_mday=31;
                }
                else{
                    tminfo->tm_mon-=1;
                    if (tminfo->tm_mon == 3 || tminfo->tm_mon == 5 || tminfo->tm_mon == 8 || tminfo->tm_mon == 10)
                        tminfo->tm_mday=30;
		
                    else if (tminfo->tm_mon == 1){
                    bool leapyear = (tminfo->tm_year % 4 == 0 && tminfo->tm_year % 100 != 0) || (tminfo->tm_year % 400 == 0);

                        if (leapyear == 0)
                            tminfo->tm_mday= 28;
                        else tminfo->tm_mday= 29;
                    }
                    else  tminfo->tm_mday = 31;
                }
            }
            else tminfo->tm_mday-=1;
        }
    }
    std::string RCTS(std::string pattern="%Y-%m-%d %H:%M:&S"){//Return time to string on a dictated pattern
        char dat[11];
        strftime (dat,11,pattern.c_str(),tminfo);
        dateS=dat;
        return dateS;
    }

};

class CRN{
    private:
        struct timeval t1, t2;
        double elapsedTime;
    public:
        void STRT(){
            gettimeofday(&t1, NULL);
        }
        
        void STP(){
            gettimeofday(&t2, NULL);
        }
        
        double LPS(){//en milisegundos
        elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
        elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
        return elapsedTime;
        }

};

#endif /* QUANDL_H_ */
