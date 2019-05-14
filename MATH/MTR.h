#ifndef MTR_H_INCLUDED
#define MTR_H_INCLUDED

//Cálculo matricial

std::vector<std::vector<double>> SM(std::vector<std::vector<double>> A,std::vector<std::vector<double>> B){//Suma matricial
   std::vector<std::vector<double>> R;
    for(int f=0;f<A.size();f++){
        R.push_back(SV(A[f],B[f]));
    }
    return R;
}

std::vector<std::vector<double>> RM(std::vector<std::vector<double>> A,std::vector<std::vector<double>> B){//Resta matricial
   std::vector<std::vector<double>> R;
    for(int f=0;f<A.size();f++){
        R.push_back(RV(A[f],B[f]));
    }
    return R;
}

std::vector<std::vector<double>> PEM(std::vector<std::vector<double>> A,double e){//Producto escalar matricial
   std::vector<std::vector<double>> R;
    for(int f=0;f<A.size();f++){
        R.push_back(PEV(A[f],e));
    }
    return R;
}

std::vector<std::vector<double>> PM(std::vector<std::vector<double>> A,std::vector<std::vector<double>> B){//Producto matricial
    
    if(A[0].size()!=B.size()){
        std::cout<<"Producto matricial no posible"<<std::endl;
        exit (EXIT_FAILURE);
    }
    
   std::vector<std::vector<double>> R;
   std::vector<double> Rt;
   double Pt;
   double St;
    for(int f=0;f<A.size();f++){
        for(int c=0;c<B[0].size();c++){
            for(int ic=0;ic<A[f].size();ic++){
                Pt=A[f][ic]*B[ic][c];
                St+=Pt;
            }
            Rt.push_back(St);
            St=0;
        }
        R.push_back(Rt);
        Rt.clear();
    }
    return R;
}

std::vector<std::vector<double>> SWP(std::vector<std::vector<double>>M, int a, int b){//SWAP rows of a matrix
    std::vector<std::vector<double>> K;
    K.clear();
    for (int i=0;i<M.size();i++){
        if(a==i){K.push_back(M[b]);}
        else if(b==i){K.push_back(M[a]);}
        else{K.push_back(M[i]);}
    }
    return K;
}

std::vector<std::vector<double>> TRS(std::vector<std::vector<double>>M){//Devuelve la traspuesta de la matriz
    std::vector<std::vector<double>> K;
    //DBG_STD(M,"TRS");
    
    for(int i=1;i<M.size();i++){
        if(M[i-1].size()!=M[i].size()){
            std::cout<<"MTR_M_SIZE_ERROR: "<<i<<"::"<<M[i-1].size()<<"->"<<M[i].size()<<std::endl;
            exit(-1);
        }
    }
    
    if(M.size()>0&&M[0].size()>0){
        for(int i=0;i<M[0].size();i++){
            std::vector<double>k;
            for(int c=0;c<M.size();c++){
                k.push_back(M[c][i]);
            }
            K.push_back(k);
        }
    }
    else{
        std::cout<<"MATH_MTR_TRS_VECT_ERROR"<<std::endl;
        exit(-1);
    }
    return K;

}

std::vector<std::vector<double>> PIV(std::vector<std::vector<double>>M, int fId){//Algoritmo de pivoteo matricial
    if(M[fId][fId]==0){
            for(int i=fId+1;i<M.size();i++){
                if(M[i][fId]!=0){
                    std::swap(M[fId],M[i]);
                    M[i]=PEV(M[i],-1);
                    return M;
                }
            }
        }
        return M;
	} 
	
std::vector<std::vector<double>> GAUSS_ESC(std::vector<std::vector<double>> M){//Método de gaus para obtenr matriz escalonada
    double PP=0;
    for(int f=0;f<M.size()-1;f++){
         M=PIV(M,f);
        for(int fe=f+1;fe<M.size();fe++){
                if((M[f][f]!=0)&&(M[fe][f]!=0)){//Si existe pivoteo posible
            PP=(M[fe][f]/M[f][f]);
            M[fe]=RV(M[fe],PEV(M[f],PP));
                }
        }        
    }
    
    for(int f=1;f<M.size();f++){//comprobación
        for(int c=0;c<f;c++){
        if(M[f][c]!=0)M=GAUSS_ESC(M);
        }
    }
    
    return M;
}

std::vector<std::vector<double>> GAUSS_ESC_R(std::vector<std::vector<double>>M){//Método de gaus para obtenr matriz escalonada reducida
        std::vector<std::vector<double>> R=M;
    
    for(int f=0;f<M.size()-1;f++){
        for(int fe=f+1;fe<M.size();fe++){
            R[fe]=RV(R[fe],PEV(R[f],(R[fe][f]/R[f][f])));
        }        
    }

    
    for(int f=M.size()-1;f>0;f--){
        for(int fe=f-1;fe>=0;fe--){
            if(R[f][f]!=0)
            R[fe]=RV(R[fe],PEV(R[f],(R[fe][f]/R[f][f])));
        }        
    }
    
    
    
    return R;
}


double DET(std::vector<std::vector<double>> M){//Devuelve el determinante de la matriz
            std::vector<std::vector<double>> MES=GAUSS_ESC(M);
                double Dt=1;
            for(int f=0;f<MES.size();f++){
                    Dt*=MES[f][f];
                }
                return Dt;
}


std::vector<double> GAUSS_SS(std::vector<std::vector<double>>M,std::vector<double>b);
std::vector<std::vector<double>> INV(std::vector<std::vector<double>> M){//Método matriz inversa por resolucion de sistemas, poco eficiente
    std::vector<std::vector<double>> In=M;
    std::vector<double> sT;
    std::vector<double> SsT;
    
    for(int i=0;i<M.size();i++){
        sT.clear();
        for (int id=0;id<M[0].size();id++){
            if(id==i){sT.push_back(1);}
            else{sT.push_back(0);}
        }
        
        SsT=GAUSS_SS(M,sT);
        
        for(int ins=0;ins<SsT.size();ins++){
            In[ins][i]=SsT[ins];
        }
        
        
    }
return In;
}

#endif
