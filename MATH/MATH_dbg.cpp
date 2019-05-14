#include <vector>
#include <math.h>   // exp
#include <stdlib.h> // rand
#include <time.h>

#include <fstream>
#include <string>

#include <algorithm>

#include <iostream> //cout,cin

#include "MATH.h"

class cmplxFn{
    
};

double funct(double x){
    return x*x;
}

double funct2(std::vector<double> pnt){
    double z=1;
    for (int p=0;p<pnt.size();p++){
        z*=pnt [p];
    }
    return z;
}

double optf2(std::vector<double> pnt){
    double z=1;
    for (int p=0;p<pnt.size();p++){
        z*=1+(pnt[p]*pnt[p]);
    }
    return z;
}

int main() {
    
    //Testeo de calculo vectorial y matricial
std::vector<std::vector<double>> M{{1,3,8,},{5,0,7,},{7,8,9,}};
std::vector<double> b={3,4,6};
std::vector<std::vector<double>> P{{1,0,0},{0,0,1},{0,1,0}};
//std::vector<std::vector<double>> PR=PM(M,P);
//std::vector<std::vector<double>> Mrref=GAUSS_ESC_R(M);


//Mer=GAUSS_ESC(Mer);

std::cout<<"M:"<<std::endl;
for (int f=0; f<M.size();f++){
    for(int c=0; c<M[f].size();c++){
        std::cout << M[f][c]<<" ";
    }
        std::cout<<std::endl;
}

/*std::cout<<"PR:"<<std::endl;
for (int f=0; f<PR.size();f++){
    for(int c=0; c<PR[f].size();c++){
        std::cout << PR[f][c]<<" ";
    }
        std::cout<<std::endl;
}*/
std::vector<std::vector<double>> Mer=GAUSS_ESC(M);
//std::vector<std::vector<double>> Mer=M;
  std::cout<<"ER:"<<std::endl;  
for (int f=0; f<Mer.size();f++){
    for(int c=0; c<Mer[f].size();c++){
        std::cout << Mer[f][c]<<" ";
    }
    std::cout<<std::endl;
}


std::vector<double> x=GAUSS_SS(M,b);
//std::vector<std::vector<double>> Mer=M;
  std::cout<<"x:"<<std::endl;  
for (int f=0; f<x.size();f++){

        std::cout << x[f]<<" ";

}
    std::cout<<std::endl;
 /* std::cout<<"RREF:"<<std::endl;  
for (int f=0; f<Mrref.size();f++){
    for(int c=0; c<Mrref[f].size();c++){
        std::cout << Mrref[f][c]<<" ";
    }
    std::cout<<std::endl;
}*/

  std::cout<<"DET:"<<std::endl;
  std::cout<<DET(M)<<std::endl;
    
  
std::vector<std::vector<double>>inv=INV(M);
    std::cout<<"INV:"<<std::endl;  
for (int f=0; f<inv.size();f++){
    for(int c=0; c<inv[f].size();c++){
        std::cout << inv[f][c]<<" ";
    }
    std::cout<<std::endl;
}
    //Testeo de calculo vectorial y matricial



//Testeo de calculo diferencial

  std::cout<<"DERIV:"<<std::endl;
  std::cout<<DRV2(funct,20)<<std::endl;
  
  std::cout<<"INTG:"<<std::endl;
  std::cout<<INT(funct,0,1,10)<<std::endl;

  
  std::vector<double> grad=GRAD(optf2,{5,9,677,987,12,78,1,2,33});
//std::vector<std::vector<double>> Mer=M;
  std::cout<<"GRAD:"<<std::endl;  
for (int f=0; f<grad.size();f++){
        std::cout << grad[f]<<" ";
}
  std::cout<<std::endl;
  
  std::vector<std::vector<double>> Hess=HESS(funct2,{0,0});
    std::cout<<"HESS:"<<std::endl;  
for (int f=0; f<Hess.size();f++){
    for(int c=0; c<Hess[f].size();c++){
        std::cout << Hess[f][c]<<" ";
    }
    std::cout<<std::endl;
}
//Testeo de calculo diferencial

//Testeo de optimizadores
std::vector<double> result=GDO(optf2,{5,9,677,987,12,78,1,2,33},1000000,1.1);

  std::cout<<"OPT:"<<std::endl;  
for (int f=0; f<result.size();f++){
        std::cout <<result[f]<<" ";
}
  std::cout<<std::endl;
  
    std::cout<<"OPT R:"<<optf2(result)<<std::endl;  
//Testeo de optimizadores

	return 0;
}
