#ifndef STA_H_INCLUDED
#define STA_H_INCLUDED
//Statistics library

double MEAN(std::vector<double> val){

    if(val.size()>=1){
    double medi=0;
    for(int i=0;i<val.size();i++){
        medi+=val[i];
    }
    medi=medi/val.size();
    
    return medi;
        
    }
    else return 0;
}

double MEAN(std::vector<std::vector<double>> val,int valID){

    if(val.size()>1){
    double medi=0;
    for(int i=0;i<val.size();i++){
        medi+=val[i][valID];
    }
    medi=medi/val.size();
    
    return medi;
        
    }
    else return 0;
}

double ST_DEV(std::vector<double> val){

    if(val.size()>=1){    
    double medi=MEAN(val);
    double st_dev=0;
    for(int i=0;i<val.size();i++){
        st_dev+=pow((val[i]-medi),2);
    }
    st_dev=st_dev/val.size();
    st_dev=sqrt(st_dev);
    
    return st_dev;
        
    }
    else return -1;
    }
    
    double ST_DEV(std::vector<std::vector<double>> val,int valID){

    if(val.size()>2){    
    double medi=MEAN(val,valID);
    double st_dev=0;
    for(int i=0;i<val.size();i++){
        st_dev+=pow((val[i][valID]-medi),2);
    }
    st_dev=st_dev/val.size();
    st_dev=sqrt(st_dev);
    
    return st_dev;
        
    }
    else return -1;
    }


#endif