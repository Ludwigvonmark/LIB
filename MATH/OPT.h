#ifndef OPT_H_INCLUDED
#define OPT_H_INCLUDED
#include <iomanip> 

//Optimization algorithms
std::vector<double> S_GDO(std::function<double(std::vector<double>)> fun, std::vector<double>X0,int MxIt, double min){ 
    std::vector<double>Xk=X0;
    std::vector<double>Dk=X0;//Direccion de descenso
    
    double fnxk;
    
    std::vector<double>GRD;
    double NrGr;
           
    for(int i=0;(i<MxIt);i++){
        
        GRD=GRAD(fun,Xk);
        NrGr=NORM(GRD);
        //std::cout<<"NORM: "<<NrGr<<std::endl;
        fnxk=fun(Xk);
                
        if((NrGr<0.00001)||(fnxk<min)){
                  // std::cout<<"NORM: "<< std::setprecision(15)<<NrGr<<std::endl;
       //std::cout<<"fn: "<< std::setprecision(15)<<fun(Xk)<<std::endl;
            return Xk;
        }
        else{
           /* for(int k=0;k<Dk.size();k++){//Calculo de la dirección
                Dk[k]=-1*(((double)GRD[k])/((double)NrGr));
            }*/
            Dk=PEV(GRD,-0.00001);
            
            if(fun(SV(Xk,Dk))>fnxk){
                return Xk;
            }
            Xk=SV(Xk,Dk);
        }
        
       
       /*//dbg
                    std::cout<<"Xk: ";
            for(int w=0;w<Xk.size();w++){std::cout<<Xk[w]<<" ";}
            std::cout<<std::endl;
                                std::cout<<"Dk: ";
            for(int w=0;w<Dk.size();w++){std::cout<<Dk[w]<<" ";}
            std::cout<<std::endl;
            //dbg*/
       
       std::cout<<"ITER: "<< i<<std::endl;
       std::cout<<"NORM: "<< std::setprecision(20)<<NrGr<<std::endl;
       std::cout<<"fn: "<< std::setprecision(20)<<fun(Xk)<<std::endl<<std::endl;
       //dbg*/
    }
    
}

std::vector<double> NEUR_GDO(std::function<double(std::vector<double>)> fun, std::vector<double>X0,int MxIt, double min){//Gradient descent optimicer A1 for sigmoid functions.
    std::vector<double>Xk=X0;
    std::vector<double>Dk=X0;//Direccion de descenso

        std::vector<double>fnv;
        
    
    double Tk;//Paso de descenso
    const double s=1.001;
    const double B=0.05255;
    int p=0;
    
    double fnxk;
    //double minfnxk=s;
    
    std::vector<double>GRD;
    double NrGr;
           
    for(int i=0;(i<MxIt);i++){
        Tk=s;
        p=0;
        fnxk=fun(Xk);
        GRD=GRAD(fun,Xk);
        NrGr=NORM(GRD);
        if(i>2)
        fnv.push_back(fnxk);
       /* std::cout<<"NORM: "<<NrGr<<std::endl;
        std::cout<<"fn: "<< std::setprecision(20)<<fnxk<<std::endl<<std::endl;*/
        //if(fnxk<minfnxk)minfnxk=fnxk;
        
        //if(NrGr<1e-5){//Small Gradient trigger 
        if(((double)fnxk/NrGr)>1e4){//Small improvment trigrer    
                  // std::cout<<"NORM: "<< std::setprecision(15)<<NrGr<<std::endl;
       //std::cout<<"GRD<eps"<<std::endl;

            return Xk;
        }
        else if(fnxk<min){
            //std::cout<<"Func Solv"<<std::endl;

            return Xk;
        }
        else{
            for(int k=0;k<Dk.size();k++){//Calculo de la dirección
                Dk[k]=-1*(((double)GRD[k])/((double)NrGr));
            }
            //Dk=PEV(GRD,-1);
                while(fun(SV(Xk,PEV(Dk,Tk)))>fnxk){//Cálculo del paso
                    p++;
                    Tk=s*pow(B,p);
               //std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            }

        }
        
       Xk=SV(Xk,PEV(Dk,Tk));
       
       /*for(int lw=0;lw<Xk.size();lw++){//Limit for sigmoid function, -1<W_i<1 *Lowers the performance, more acurate result.* This needs work. 
           if(Xk[lw]>=1)Xk[lw]=1;
           else if(Xk[lw]<=-1)Xk[lw]=-1;
        }*/
       
       //dbg
                    /*std::cout<<"Xk: ";
            for(int w=0;w<Xk.size();w++){std::cout<<Xk[w]<<" ";}
            std::cout<<std::endl;
                                std::cout<<"Dk: ";
            for(int w=0;w<Dk.size();w++){std::cout<<Dk[w]<<" ";}
            std::cout<<std::endl;
            std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            //dbg*/
              if(i%50==0){
       std::cout<<"ITER: "<< i<<std::endl;
       std::cout<<"|Grad|_2: "<< std::setprecision(26)<<NrGr<<std::endl;
       std::cout<<"fn: "<< std::setprecision(26)<<fun(Xk)<<std::endl<<std::endl;
       

            }
           
                
            
       //dbg*/
        }

    return Xk;
    
}

std::vector<double> NEUR_GDO(std::function<double(std::vector<double>)> fun, std::vector<double>X0,int MxIt, double min,double GrdLmt, double s=1.001, double B=0.05255,double* CNG=0, double* CFV=0 ){//Gradient descent optimicer A1 for sigmoid functions.
    std::vector<double>Xk=X0;
    std::vector<double>Dk=X0;//Direccion de descenso

    std::vector<double>fnV;
    double frsDER=1;
    std::vector<double>nrgrV;
    double secDER=1;
        
    
    double Tk;//Paso de descenso
    //const double s=1.001;
    //const double B=0.05255;
    int p=0;
    
    double fnxk;
    //double minfnxk=s;
    
    std::vector<double>GRD;
    double NrGr;
           
    for(int i=0;(i<MxIt);i++){
        Tk=s;
        p=0;
        fnxk=fun(Xk);
        GRD=GRAD(fun,Xk);
        NrGr=NORM(GRD);
        
        //if(i>2)
        fnV.push_back(fnxk);//Aproximation od first derivate
        nrgrV.push_back(NrGr);//Aproximation of second derivate
        if(nrgrV.size()>1){
            frsDER=fnV[0]-fnV[1];
            fnV.clear();
            secDER=nrgrV[0]-nrgrV[1];
            nrgrV.clear();
        }
        
       /* std::cout<<"NORM: "<<NrGr<<std::endl;
        std::cout<<"fn: "<< std::setprecision(20)<<fnxk<<std::endl<<std::endl;*/
        //if(fnxk<minfnxk)minfnxk=fnxk;
        
        //if(NrGr<1e-5){//Small Gradient trigger 
        if(((double)fnxk/NrGr)>GrdLmt||(frsDER==0&&secDER==0)){//Small improvment trigrer    
                  // std::cout<<"NORM: "<< std::setprecision(15)<<NrGr<<std::endl;
       //std::cout<<"GRD<eps"<<std::endl;

            return Xk;
        }
        else if(fnxk<min){
            //std::cout<<"Func Solv"<<std::endl;

            return Xk;
        }
        else{//Minimization optimization
            for(int k=0;k<Dk.size();k++){//Calculo de la dirección
                Dk[k]=-1*(((double)GRD[k])/((double)NrGr));
            }
            //Dk=PEV(GRD,-1);
                while((fun(SV(Xk,PEV(Dk,Tk)))>fnxk)/*&&Tk!=0*/){//Cálculo del paso
                    p++;
                    Tk=s*pow(B,p);
               //std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            }

        }
        
       Xk=SV(Xk,PEV(Dk,Tk));

       
       /*//dbg
                    std::cout<<"Xk: ";
            for(int w=0;w<Xk.size();w++){std::cout<<Xk[w]<<" ";}
            std::cout<<std::endl;
                                std::cout<<"Dk: ";
            for(int w=0;w<Dk.size();w++){std::cout<<Dk[w]<<" ";}
            std::cout<<std::endl;
            std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            //dbg*/

                    
              if(i%((int)MxIt/10)==0){
       std::cout<<"ITER: "<< i<<std::endl;
       std::cout<<"|Grad|_2: "<< std::setprecision(20)<<NrGr<<std::endl;
       std::cout<<"~~DERIV: "<< std::setprecision(20)<<frsDER<<std::endl;
       std::cout<<"~~HESSIAN: "<< std::setprecision(20)<<secDER<<std::endl;
       std::cout<<"fn: "<< std::setprecision(20)<<fnxk<<std::endl;

                   }
       //dbg*/
        }
    *CNG=NrGr;
    *CFV=fnxk;
    return Xk;
    
}

std::vector<double> V_GDO(std::function<double(std::vector<double>)> fun, std::vector<double>X0,int MxIt, double min){//Gradient descent optimicer A1
    std::vector<double>Xk=X0;
    std::vector<double>Xt=X0;
    std::vector<double>Dk=X0;//Direccion de descenso
    std::vector<double>Tk=X0;//Paso de descenso
    
    //double Tk;//Paso de descenso
    const double s=1000;
    const double B=0.05255;
    int p=0;
    
    double fnxk;

    std::vector<double>GRD;
    double NrGr;
           
    for(int i=0;(i<MxIt);i++){
        for(int i=0;i<Tk.size();i++){Tk[i]=s;}
        //Tk=s;
        //p=0;
        
        GRD=GRAD(fun,Xk);
        NrGr=NORM(GRD);
        //std::cout<<"NORM: "<<NrGr<<std::endl;
        fnxk=fun(Xk);
        //if(fnxk<minfnxk)minfnxk=fnxk;
        
        if((NrGr<0.00001)||(fnxk<min)){
                  // std::cout<<"NORM: "<< std::setprecision(15)<<NrGr<<std::endl;
       //std::cout<<"fn: "<< std::setprecision(15)<<fun(Xk)<<std::endl;
            return Xk;
        }
        else{
            for(int k=0;k<Dk.size();k++){//Calculo de la dirección
                Dk[k]=-1*(((double)GRD[k])/((double)NrGr));
            }

            for(int ps=0;ps<Tk.size();ps++){//Calculo del paso
                p=0;
                Xt=Xk;
                Xt[ps]=Xk[ps]+(Dk[ps]*Tk[ps]);
                while(fun(Xt)>fnxk){
                    p++;
                    Tk[ps]=s*pow(B,p);
                    Xt[ps]=Xk[ps]+(Dk[ps]*Tk[ps]);
               //std::cout<<"TK: "<< std::setprecision(20)<<Tk[ps]<<std::endl;
            }
            Xk[ps]=Xt[ps];
        }
            
        }
        
       //dbg
                    /*std::cout<<"Xk: ";
            for(int w=0;w<Xk.size();w++){std::cout<<Xk[w]<<" ";}
            std::cout<<std::endl;
                    std::cout<<"Dk: ";
            for(int w=0;w<Dk.size();w++){std::cout<<Dk[w]<<" ";}
            std::cout<<std::endl;
                    std::cout<<"Tk: ";
            for(int w=0;w<Tk.size();w++){std::cout<<Tk[w]<<" ";}
            std::cout<<std::endl;
            //dbg*/
       if(50%i==0){
       std::cout<<"ITER: "<< i<<std::endl;
       std::cout<<"NORM: "<< std::setprecision(20)<<NrGr<<std::endl;
       std::cout<<"fn: "<< std::setprecision(20)<<fun(Xk)<<std::endl<<std::endl;
       //dbg*/
       }
    }
    return Xk;
}

std::vector<double> BFGS(std::function<double(std::vector<double>)> fun,std::vector<double> X0,int MxIt, double min){
    std::vector<double>Xk=X0;
    std::vector<double>Xk1=X0;
     //std::vector<std::vector<double>>xk1;
    std::vector<double>Dk=X0;//Direccion de descenso

    
    double Tk;//Paso de descenso
    const double s=1000;
    const double B=0.05255;
    const double e=0.7255;
    int p=0;
    
    std::vector<double>GRD;
    std::vector<std::vector<double>>Grd;
    double NrGr;
    std::vector<std::vector<double>>Hss;
           
    for(int i=0;(i<MxIt);i++){
        Tk=s;
        p=0;
        
        Grd.clear();
        GRD=GRAD(fun,Xk);
        Grd.push_back(GRD);
        Hss=HESS(fun,Xk);
        Hss=INV(Hss);
        NrGr=NORM(GRD);
        //std::cout<<"NORM: "<<NrGr<<std::endl;
        
        if((NrGr<eps)||(fun(Xk)<min)){
                  // std::cout<<"NORM: "<< std::setprecision(15)<<NrGr<<std::endl;
       //std::cout<<"fn: "<< std::setprecision(15)<<fun(Xk)<<std::endl;
            return Xk1;
        }
        else{
            Xk1=PM(Hss,Grd)[0];
            Xk1=PEV(Xk1,-1);
            /*for(int k=0;k<Dk.size();k++){//Calculo de la dirección
                Dk[k]=-1*(((double)GRD[k])/((double)NrGr));
            }*/
            //Dk=PEV(GRD,-1);
            
            
            
            while((fun(SV(Xk,PEV(Xk1,Tk))))>(fun(Xk))){//Calculo del paso
                p++;
                Tk=s*pow(B,p);
               // std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            }
        }
        
       Xk1=SV(Xk1,PEV(Dk,Tk));
       
                 /*   std::cout<<"Xk: ";
            for(int w=0;w<Xk.size();w++){std::cout<<Xk[w]<<" ";}
            std::cout<<std::endl;
                                std::cout<<"Dk: ";
            for(int w=0;w<Dk.size();w++){std::cout<<Dk[w]<<" ";}
            std::cout<<std::endl;
            std::cout<<"TK: "<< std::setprecision(20)<<Tk<<std::endl;
            //dbg
       
       std::cout<<"ITER: "<< i<<std::endl;
       std::cout<<"NORM: "<< std::setprecision(20)<<NrGr<<std::endl;
       std::cout<<"fn: "<< std::setprecision(20)<<fun(Xk)<<std::endl<<std::endl;*/
    }
    return Xk1;
}

#endif 
