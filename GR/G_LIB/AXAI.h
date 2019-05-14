#ifndef AXAI_H_INCLUDED
#define AXAI_H_INCLUDED

class AXNN{

};


class AXAI{
AXH *AXIS;
int Finst;

int rtsp;
int rcsp;

public:

AXAI(AXH &AXISAI){
AXIS=&AXISAI;
}

~AXAI(){

}

void rspeed(){

}

void forceblock (){
if(AXIS->AN.A*AXIS->XN.NF>AXIS->AN.AI){AXIS->EME=true;}
else if(AXIS->AN.A*(AXIS->YN.NF*1)>AXIS->AN.AI){AXIS->EME=true;}
else if(AXIS->AN.A*(AXIS->ZN.NF*1)>AXIS->AN.AI){AXIS->EME=true;}
else{AXIS->EME=false;}

//if(AXIS->AN.A>AXIS->AN.AI){AXIS->EME=true;}
//else{AXIS->EME=false;}
}

void forcespeed (){
/*if(AXIS->EME){
if(AXIS->F.AI!=0){

}
}
else{
AXIS->F.AI=AXIS->AN.A*
}*/


}

void u (){
forceblock();
forcespeed();
rspeed();
}

};


#endif // AXAI_H_INCLUDED
