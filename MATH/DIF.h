#ifndef DIF_H_INCLUDED
#define DIF_H_INCLUDED

//Métodos de diferenciacion, integracion y calculo diferencial numericos

const double eps=1e-10;

//f:R->R
double DRV(std::function<double(double)> fun, double point){
    double fe;
    double fa;
    
    double derv;
    
    fe = fun(point-eps);
            //dbg
            //std::cout<<"f= "<<f;
            //dbg
    fa = fun(point+eps);
            //dbg
            //std::cout<<" fh= "<<fh;
            //dbg

    derv = (double)(fa - fe) / (double)(2*eps);//derivada parcial centrada degun la definición
            //dbg
            //std::cout<<" G= "<<(double)(fh - f) / (double)(2*eps)<<std::endl;
            //dbg
    return derv;
}

double DRV2(std::function<double(double)> fun, double point){
    double fe;
    double fa;
    
    double derv;
    
    fe = DRV(fun,point-eps);
            //dbg
            //std::cout<<"f= "<<f;
            //dbg
    fa =  DRV(fun,point+eps);
            //dbg
            //std::cout<<" fh= "<<fh;
            //dbg

    derv = (double)(fa - fe) / (double)(2*eps);//derivada parcial centrada degun la definición
            //dbg
            //std::cout<<" G= "<<(double)(fh - f) / (double)(2*eps)<<std::endl;
            //dbg
    return derv;
}


double INT(std::function<double(double)> fun, double iP, double fP, int n){//trapecio compuesta
    double ntg=0;
    double xi=0;
    double h=(fP-iP)/((double)n);
    for(int i=1;i<n;i++){
        ntg+=fun(iP+h*i);
    }
    ntg*=2;
    ntg+=fun(iP)+fun(fP);    
    ntg*=((fP-iP)/(double)(2*n));
    
    return ntg;
    
}
//f:R->R


//f:R^n->R
std::vector<double> GRAD(std::function<double(std::vector<double>)> fun, std::vector<double>point){//Vector gradiente
    double fe;
    double fa;
    
    double tP;
    
    std::vector<double> derv;
    std::vector<double>Xk=point;
    
    for(int i=0;i<point.size();i++){
        tP=Xk[i];
        Xk[i]=tP-eps;
        fe = fun(Xk);
            //dbg
           // std::cout<<"fe= "<<fe<<", "<<Xk[i];
            //dbg
        Xk[i]=tP+eps;
        fa = fun(Xk);
        
        Xk[i]=tP;
            //dbg
            //std::cout<<" fa= "<<fa<<", "<<point[i];
            //dbg

    derv.push_back( (double)(fa - fe) / (double)(2*eps));//derivada parcial centrada degun la definición
            //dbg
           // std::cout<<" G= "<<(double)(fa - fe) / (double)(2*eps)<<std::endl;
            //dbg
    }
    return derv;
}

std::vector<std::vector<double>> HESS(std::function<double(std::vector<double>)> fun, std::vector<double>point){//Matriz hessiana
    
    double fe;
    double  fa;
    
    std::vector<std::vector<double>> hess;
    std::vector<double> derv=point;
    
    std::vector<std::vector<double>> tEp;
    std::vector<std::vector<double>> tAp;
    
    std::vector<double> tE=point;
    std::vector<double> tA=point;

    
    for(int f=0;f<point.size();f++){
        tE[f]-=eps;
        tA[f]+=eps;
        
        for (int c=0;c<point.size();c++){
            tEp.push_back(tE);  tEp.push_back(tE);
            tAp.push_back(tA);  tAp.push_back(tA);
            
            tEp[0][c]+=eps;   tEp[1][c]-=eps;
            
            tAp[0][c]+=eps;   tAp[1][c]-=eps;
            
            fa=( (double)(fun(tAp[0]) - fun(tEp[0])) / (double)(2*eps));
            
            fe=( (double)(fun(tAp[1]) - fun(tEp[1])) / (double)(2*eps));
            
            derv[c]=( (double)(fa - fe) / (double)(2*eps));
            
            tEp.clear();
            tAp.clear();
        }
        tE[f]=point[f];tA[f]=point[f];
        hess.push_back(derv);
        
        }
        return hess;
        
    }
    
    

//f:R^n->R


//f:R^n->R^n

//f:R^n->R^n
#endif
