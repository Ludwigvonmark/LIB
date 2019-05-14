#ifndef FPL_H_INCLUDED
#define FPL_H_INCLUDED

bool FPC(float A,float B, float epsilon){
float a=A,b=B;
if (a<b){a+=epsilon;
if (a>b){return true;}}
else if (a>b){a-=epsilon;
if (a<b){return true;}}
else if(a==b){return true;}
return false;
}

float RFP(float A,float epsilon){
int d =A/epsilon;
return d*epsilon;
}



#endif // AXFPL_H_INCLUDED
