#ifndef NRM_HPP_INCLUDED
#define NRM_HPP_INCLUDED

//Data normalizer
class NRM{
public:
    double Nrt=0;//Maximun
    double Mnt=0;//Minimun
    double Rgt=0;//Rang Training data
    
    double nR=1.2;
    NRM(){
       /* Nrt=0;//Maximun
        Mnt=0;//Minimun
        Rgt=0;//Rang Training data*/
    }
    
    void ONP(std::vector<double> veec){//Obtain normalizer parametres
        if(veec.size()>0){
        //Obtain the maximuns and minimun
            Nrt=veec[0];
            Mnt=veec[0];
            for(int dbli=0;dbli<veec.size();dbli++){
                if(Nrt<veec[dbli]){
                    Nrt=veec[dbli];
                    //std::cout<<"Nrt: "<<Nrt<<std::endl;
                }
                if(Mnt>veec[dbli]){
                    Mnt=veec[dbli];
                    //std::cout<<"Mnt: "<<Mnt<<std::endl;
                }
            }
            Rgt=Nrt-Mnt;
        }
    }
    
    std::vector<double> RNV(std::vector<double> veec){//Return the normalized vector
        
        std::vector<double> normalized;
        if(Rgt>0){
            for(int c=0;c<veec.size();c++){
                normalized.push_back((double)(veec[c]-Mnt)/(Rgt*nR));
            } 
        }
        else{
            for(int c=0;c<veec.size();c++){
                normalized.push_back(0);
            }
        }
        return normalized;
    }
    
    double RN(double veec){//Return denormalized single data
        
        double denormalized;
        if(Rgt>0){
                denormalized=(double)((veec*(Rgt*nR))+Mnt);
        }
        else{
                denormalized=0;
        
        }
        return denormalized;
    }
};

#endif
