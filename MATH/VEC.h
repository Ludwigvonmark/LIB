#ifndef VEC_H_INCLUDED
#define VEC_H_INCLUDED

std::vector<double> SV(std::vector<double> A,std::vector<double> B){//Suma vectorial
   std::vector<double> R;
    for(int c=0;c<A.size();c++){
        R.push_back(A[c]+B[c]);
    }
    return R;
}

std::vector<double> RV(std::vector<double> A,std::vector<double> B){//Resta vectorial
   std::vector<double> R;
    for(int c=0;c<A.size();c++){
        R.push_back(A[c]-B[c]);
    }
    return R;
}

std::vector<double> PEV(std::vector<double> A,double e){//Producto escalar vectorial
   std::vector<double> R;
    for(int c=0;c<A.size();c++){
        R.push_back(A[c]*e);
    }
    return R;
}

double NORM(std::vector<double> A){//Norma 2 vectorial
    double sT=0;
    for (int c=0;c<A.size();c++){
        sT+=(A[c]*A[c]);
    }
    
    return sqrt(sT);
}

#endif
