#ifndef FPU_H_INCLUDED
#define FPU_H_INCLUDED

//Floating point utilities

bool FPC(float A, float B, float epsilon) {
	float a = A, b = B;
	if (a<b) {
		a += epsilon;
		if (a>b) { return true; }
	}
	else if (a>b) {
		a -= epsilon;
		if (a<b) { return true; }
	}
	else if (a == b) { return true; }
	return false;
}

bool IPC(int A, int B, float epsilon) {
	int a = A, b = B;
	if (a<b) {
		a += epsilon;
		if (a>b) { return true; }
	}
	else if (a>b) {
		a -= epsilon;
		if (a<b) { return true; }
	}
	else if (a == b) { return true; }
	return false;
}

float RFP(float A, float epsilon) {
	int d = A / epsilon;
	return d*epsilon;
}




int RIP(double data, int multip ,int prec){//Devuelve un entero de la precisón y escala dadas apartir de un decimal multip 1000, prec 5 
    int r1=(int)data*(multip/10);
    int r2=(int)data*(multip);
    int r3=r2-r1;
    
    r1=r1*10;//Dato a devolver con ultima cifra 0
    
if (r3>prec){
    if(r3>prec+(prec/2)){return r1+10;}
    else if(r3<prec+(prec/2)){return r1+5;}
    
}

else if(r3<prec){
    if(r3>prec-(prec/2)){return r1+5;}
    else if(r3<prec-(prec/2)){return r1;}
    
}
    else{
        return r1*10;
    }
    
}
int RIP(float data, int multip ,int prec){//Devuelve un entero de la precisón y escala dadas apartir de un decimal multip 1000, prec 5 
    int r1=(int)data*(multip/10);
    int r2=(int)data*(multip);
    int r3=r2-r1;
    
    r1=r1*10;//Dato a devolver con ultima cifra 0
    
if (r3>prec){
    if(r3>prec+(prec/2)){return r1+10;}
    else if(r3<prec+(prec/2)){return r1+5;}
    
}

else if(r3<prec){
    if(r3>prec-(prec/2)){return r1+5;}
    else if(r3<prec-(prec/2)){return r1;}
    
}
    else{
        return r1*10;
    }
    
}


int RIP(int data,int prec){//Devuelve un entero de la precisón y escala dadas apartir de un decimal multip 1000, prec 5 
    int r1=data/10;
    r1=r1*10;
    int r2=data;
    int r3=r2-r1;
    
    
if (r3>prec){
    if(r3>prec+(prec/2)){return r1+10;}
    else if(r3<prec+(prec/2)){return r1+5;}
    
}

else if(r3<prec){
    if(r3>prec-(prec/2)){return r1+5;}
    else if(r3<prec-(prec/2)){return r1;}
    
}
    else{
        return r2;
    }
    
}

#endif
