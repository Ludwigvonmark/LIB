#ifndef SLV_H_INCLUDED
#define SLV_H_INCLUDED

//Solver algorithms

std::vector<double> GAUSS_SS(std::vector<std::vector<double>>M){//Método de gaus para resolución de sistemas lineales, M matriz ampliada
    M=GAUSS_ESC(M);
            std::vector<double> x;
    for (int b=0;b<M.size();b++){
        x.push_back(M[b][M.size()-1]);
    }

        double rT=0;
        
        if(M.size()+1<M[0].size()){
            std::cout<<"Sistema indeterminado";
            exit (EXIT_FAILURE);
        }
        
        for(int i=M.size()-1;i>=0;i--){
            rT=M[i][M[0].size()-1];
            for(int j=i+1;j<M.size();j++){
                rT-=(x[j]*M[i][j]);
            }
            
            x[i]=rT/M[i][i];
            
        }
        return x;
}

std::vector<double> GAUSS_SS(std::vector<std::vector<double>>M,std::vector<double>b){//Método de gaus para resolución de sistemas lineales, M matriz de funciones, b matriz de coeficientes
    std::vector<std::vector<double>>Ma=M;
    
    for(int f=0;f<M[0].size();f++){
        Ma[f].push_back(b[f]);
    }

    return GAUSS_SS(Ma);
}




#endif
