#ifndef AXUI_H_INCLUDED
#define AXUI_H_INCLUDED

class AXTOP{
char BTXT[7][8];
bool group1;
button file;
button edit;

button config;
button view;
button render;
button help;

button newf;
button openf;
button savef;

public:

button object;

bool all=true;
AXTOP(){
snprintf(BTXT[0],8,"File");
snprintf(BTXT[1],8,"Edit");
snprintf(BTXT[2],8,"Object");
snprintf(BTXT[3],8,"Config");
snprintf(BTXT[4],8,"View");
snprintf(BTXT[5],8,"Render");
snprintf(BTXT[6],8,"Help");
file.click=true;
edit.click=false;
object.click=false;
config.click=false;
view.click=false;
render.click=false;
help.click=false;
}

void draw(struct ICONST icon,TTF_Font *font,SDL_Color textColor){
glPushMatrix();
glTranslatef(0,SCREEN_HEIGHT-50,-1.0f);
glColor3f(0,0,0);
drawRect(SCREEN_WIDTH,50);
glTranslatef(8.0,30.0,0.0);

group1=file.over||edit.over||object.over||config.over||view.over||render.over;

file.dTSWB(font,textColor,BTXT[0],group1);
glTranslatef((file.bon[1]-file.bon[0])+10,0.0,0.0);
edit.dTSWB(font,textColor,BTXT[1],group1);
glTranslatef((edit.bon[1]-edit.bon[0])+10,0.0,0.0);
object.dTSWB(font,textColor,BTXT[2],group1);
glTranslatef((object.bon[1]-object.bon[0])+10,0.0,0.0);
config.dTSWB(font,textColor,BTXT[3],group1);
glTranslatef((config.bon[1]-config.bon[0])+10,0.0,0.0);
view.dTSWB(font,textColor,BTXT[4],group1);
glTranslatef((view.bon[1]-view.bon[0])+10,0.0,0.0);
render.dTSWB(font,textColor,BTXT[5],group1);
glTranslatef((render.bon[1]-render.bon[0])+20,0.0,0.0);
help.dTSTB(font,textColor,BTXT[6]);

glPopMatrix();
}
};

class AXD{

sedtext X;
sedtext Y;
sedtext Z;
sedtext U;
sedtext V;
sedtext W;

sedtext S;
sedtext T;
sedtext C;//consumo electrico
sedtext N;
sedtext P;//signal delay
sedtext D;//db
sedtext E;//power eficiency
sedtext G;//sistem temperature

button drag;
button close;

button more;
button minu;
button cero;
button block;

scrollold dscroll;

//scroll APDS;

char DTt[9];

GLfloat mtxpos[16];

public:
bool isdragg=false;
bool collision=false;
float scro=190;
float bon[4];
float pos[2]={0,0};
double rpos[2];

float AXFRAMERATE;

//AXD(float x,float y){
//rpos[0]=x;
//rpos[1]=y;
//}

void updateData(AXH AXISD){
snprintf(DTt,9,"%f",AXISD.X.A);
snprintf(X.etext,15,"X %s mm",DTt);

snprintf(DTt,9,"%f",AXISD.Y.A);
snprintf(Y.etext,15,"Y %s mm",DTt);

snprintf(DTt,9,"%f",AXISD.Z.A);
snprintf(Z.etext,15,"Z %s mm",DTt);

snprintf(DTt,8,"%f",AXISD.XN.NF);
snprintf(U.etext,15,"U %s mm/s",DTt);

snprintf(DTt,9,"%f",AXISD.YN.NF);
snprintf(V.etext,15,"V %s RPM",DTt);

snprintf(DTt,9,"%f",AXISD.ZN.NF);
snprintf(W.etext,15,"W %s W/h",DTt);

snprintf(DTt,9,"%f",AXISD.db.S);
snprintf(S.etext,15,"M %s db",DTt);

snprintf(DTt,9,"%f",AXISD.WAT.S);
snprintf(T.etext,15,"W %s W/h",DTt);

snprintf(DTt,8,"%f",AXISD.FedR);
snprintf(C.etext,15,"F %s mm/m",DTt);

snprintf(DTt,9,"%f",AXISD.RPM.S);
snprintf(N.etext,15,"S %s RPM",DTt);

snprintf(DTt,9,"%f",AXFRAMERATE);
snprintf(P.etext,15,"C %s ms",DTt);

snprintf(DTt,9,"%f",AXISD.T.S);
snprintf(D.etext,15,"T %s C",DTt);

snprintf(DTt,9,"%f",AXISD.AXNW);
snprintf(E.etext,15,"N %s N",DTt);

snprintf(DTt,9,"%f",0);
snprintf(G.etext,15,"N %s N",DTt);
}

void d(struct ICONST icon,TTF_Font *font,TTF_Font *sfont,SDL_Color textColor,SDL_Color dcol,SDL_Color ocol){
dragpan(drag.click,pos);
if(drag.click){
//rpos[0]=pos[0]/SCREEN_WIDTH;
//rpos[1]=pos[1]/SCREEN_HEIGHT;
//if (rpos[0]>0.85){rpos[0]=1;}
//if(rpos[1]>0.80){rpos[1]=1;}
//if (rpos[0]<0.01){rpos[0]=0;}
//if(rpos[1]<0.01){rpos[1]=0;}
isdragg=true;}
else{isdragg=false;}

//if (collision){
//rpos[0]=pos[0]/SCREEN_WIDTH;
//rpos[1]=pos[1]/SCREEN_HEIGHT;
//if (rpos[0]>0.85){rpos[0]=1;}
//if(rpos[1]>0.80){rpos[1]=1;}
//if (rpos[0]<0.01){rpos[0]=0;}
//if(rpos[1]<0.01){rpos[1]=0;}
//}

//pos[0]=SCREEN_WIDTH*rpos[0];
//pos[1]=SCREEN_HEIGHT*rpos[1];




bon[0]=pos[0];bon[1]=bon[0]+150;
bon[2]=pos[1];bon[3]=bon[2]+182;
wcolldet(bon,pos);

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glColor3f(0,0,0);
drawRect(150,182);
glTranslatef(2,168.0,0.0);
drag.dragB(sfont,dcol,ocol,textColor,"::::::::::::::::::::::::::::::::::::::");
glTranslatef(133,0.0,0.0);
close.dISTB(icon.XIC);

glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(2,330.0,0.0);

glTranslatef(0.0,(-scro*dscroll.perc),0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)X.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)Y.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)Z.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)U.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)V.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)W.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)S.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)T.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)C.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)N.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)P.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)D.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)E.d(font,textColor);
glTranslatef(0,-23.0,0.0);
glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
if(mtxpos[13]<pos[1]+150&&mtxpos[13]>pos[1]+25)G.d(font,textColor);
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(2.0,4.0,0.0f);
block.dIBKB(icon.UBLOCKIC);
glTranslatef(25.0,0.0,0.0f);
cero.dISTB(icon.REICw);
glTranslatef(70.0,0.0,0.0f);
minu.dISTB(icon.MEICw);
glTranslatef(35.0,0.0,0.0f);
more.dISTB(icon.MAICw);
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(138.0,30.0,0.0f);
dscroll.d(icon);
glPopMatrix();
}

};


class AXV {
sedtext Vt;
std::string id;
AXA *ACT;



button drag;
button close;

int conta;
int conte;
button more;
button minu;

button verif;
button cero;

button block;
char DTt[9];

GLfloat mtxpos[16];


public:
//char *edit;
char edit[9];
float step=0.005000;
float cerop;

bool isdragg=false;
bool collision=false;
float bon[4]={0,0,0,0};
float pos[2]={0,0};
double rpos[2]={0,0};

AXV(AXA &ACTA,std::string idt){
ACT=&ACTA;
id=idt;
}

void u(){
if(!more.click)conta=0;
if(!minu.click)conte=0;

if(more.click){
conta+=1;
ACT->AI+=step*conta;
}
if(minu.click){
conte+=1;
ACT->AI-=step*conte;
}

if(cero.bkclick)cerop=ACT->A;
if(!cero.click)cerop=0;

if(cero.click){
if(Vt.over||more.over||minu.over){
//snprintf(DTt,9,"%f",ACTUATOR.A);
snprintf(DTt,9,"%f",ACT->AI-cerop);
snprintf(Vt.etext,15,"%s %s mm",id.c_str(),DTt);}
else{
snprintf(DTt,9,"%f",ACT->A-cerop);
snprintf(Vt.etext,15,"%s %s mm",id.c_str(),DTt);}
}
else{
if(Vt.over||more.over||minu.over){
//snprintf(DTt,9,"%f",ACTUATOR.A);
snprintf(DTt,9,"%f",ACT->AI);
snprintf(Vt.etext,15,"%s %s mm",id.c_str(),DTt);}
else{
snprintf(DTt,9,"%f",ACT->A);
snprintf(Vt.etext,15,"%s %s mm",id.c_str(),DTt);}
}

//AXI=GETGDR(id,AXi,AXI);
//snprintf(ITt,9,"%f",AXI);
//snprintf(IT,15,"s %s mm",id.c_str(),ITt);

if(Vt.click){

snprintf(Vt.etext,15,"%s %s mm",id.c_str(),edit);
}
else{
//SDL_StopTextInput();
}

}

void d(struct ICONST icon,TTF_Font *font,TTF_Font *sfont,SDL_Color textColor,SDL_Color dcol,SDL_Color ocol){

dragpan(drag.click,pos);
if(drag.click){
isdragg=true;}
else{isdragg=false;}


bon[0]=pos[0];bon[1]=bon[0]+150;
bon[2]=pos[1];bon[3]=bon[2]+60;

wcolldet(bon,pos);


glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glColor3f(0,0,0);
drawRect(150,60);
glTranslatef(2,47.0,0.0);
drag.dragB(sfont,dcol,ocol,textColor,"::::::::::::::::::::::::::::::::::::::");
glTranslatef(133,0.0,0.0);
close.dISTB(icon.XIC);
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(5,22.0,0.0);
Vt.d(font,textColor);
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(2.0,4.0,0.0f);
verif.dISTB(icon.VERFICw);
glTranslatef(25.0,0.0,0.0f);
cero.dIBKB(icon.REICw);
glTranslatef(25.0,0.0,0.0f);
block.dIBKB(icon.UBLOCKIC);
glTranslatef(45.0,0.0,0.0f);
minu.dISTB(icon.MEICw);
glTranslatef(35.0,0.0,0.0f);
more.dISTB(icon.MAICw);
glPopMatrix();

}

};

class AXG{
etext GCODE;

etext uiline[10];

scroll gscroll;

button drag;
button close;

AXH *AXISG;

button pause;
button rev;
button rew;
button upd;
button rec;

button neww;
button op;
button sv;

text numeration[10];
char numtext[8];

std::ifstream file;
std::streampos size;

std::stringstream gpath;
std::string gline;
Uint16 aline=0;

std::stringstream gdcode;
std::string gdline;

std::vector<std::string> gcode;

public:

button play;

char * memblock;

char textline[250][10];


bool isdragg=false;
bool collision=false;
float bon[4]={0,0,0,0};
float pos[2]={0,0};
double rpos[2]={0,0};




/*
void open(){
std::string line;
  std::ifstream myfile ("AXG.ngc");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      std::cout << line << std::endl;

    }
  }

  else std::cout << "Unable to open file"<< std::endl;

}*/

void open(char* path){
file.open (path, std::ios::in|std::ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
    memblock = new char [size];

    file.seekg (0, std::ios::beg);
    file.read (memblock, size);

gpath<<memblock;
gdcode<<memblock;

while(std::getline(gdcode,gdline)){
gcode.push_back(gdline);
}

gscroll.sensibility=1/(float)gcode.size();
std::cout<<gscroll.sensibility<<std::endl;
//for (int dvd=0;dvd<gcode.size()-5000;dvd++){
//std::cout <<"abcdefghijklmnopqrs"<< gcode[dvd] <<"1234567890"<< std::endl;}


gdcode.clear();
gdcode.seekg(0, std::ios::beg);
//gdcode=std::stringstream();
//std::stringstream().swap(gdcode);

gdcode<<memblock;
//std::cout << size << std::endl;
gscroll.siz=10;

  }
  else std::cout << "Unable to open file"<< std::endl;
  //sleep(1);
}


AXG(AXH &AXHG){
AXISG=&AXHG;
GCODE.width=296;
gscroll.sensibility=0.00500;
gscroll.height=220;
gscroll.pos=0;
for(int y=0;y<10;y++)uiline[y].width=245;

}

~AXG(){
SDL_Log("expected segmentation");
if (file.is_open())
  {   file.close();
   delete[] memblock;}
}




void ut(){
/*
for(int er=0;er<10;er++){

if(aline+er<gcode.size()){
memset (&textline[er],'\n',250);
strncpy(textline[er],gcode[aline+er].c_str(),250);
}
else{
for (int es=er;es<10;es++){for(int cc=0;cc<250;cc++){textline[es][cc]=' ';}}
er=10;
}
}*/
}

void sg(float rrx,float rry,float rrz){

  std::stringstream instruction;
  instruction<<gcode[aline];
  aline++;

    while (instruction){

      std::string att;
    instruction>>att;

            if (att.compare("G0") == 0){
            if(AXISG->F.AI!=AXISG->MinFR)AXISG->MinFR=AXISG->F.AI;

   AXISG->F.AI=AXISG->MaxFR;
   AXISG->MXS=0;
    }
if (att.compare("G1") == 0){
   AXISG->F.AI=AXISG->MinFR;
AXISG->MXS=0;
    }


     if (att.compare(0,1,"X") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     AXISG->X.AI = strtod (in,0);
     AXISG->X.AI+=rrx;
    // std::cout <<AXISG.X.AI<< std::endl;
    }
        if (att.compare(0,1,"Y") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     AXISG->Y.AI = strtod (in,0);
     AXISG->Y.AI+=rry;
    }


        if (att.compare(0,1,"Z") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     AXISG->Z.AI = strtod (in,0);
     AXISG->Z.AI+=rrz;
    }

}
AXISG->X.AI=roundf(AXISG->X.AI * 200) / 200.0;
AXISG->Y.AI=roundf(AXISG->Y.AI * 200) / 200.0;
AXISG->Z.AI=roundf(AXISG->Z.AI * 200) / 200.0;
}








/*void open(){
std::ifstream file ("AXG.ngc", std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open())
  {
    size = file.tellg();
   char memblock = new char [size];
    file.seekg (0, ios::beg);
    file.read (memblock, size);
    file.close();

    std::cout << "the entire file content is in memory";

    delete[] memblock;
  }
}*/

void u(float rx,float ry,float rz){
if(play.click&&AXISG->inst){
sg(rx,ry,rz);

}

ut();

}


void d(struct ICONST icon,TTF_Font *font,TTF_Font *sfont,TTF_Font *smfont,SDL_Color textColor,SDL_Color dcol,SDL_Color ocol){


dragpan(drag.click,pos);
if(drag.click){
isdragg=true;}
else{isdragg=false;}

wcolldet(bon,pos);


if(gscroll.click){aline=gcode.size()*gscroll.perc;}
else{if(aline/gcode.size()!=0){gscroll.perc=aline/gcode.size();}
}



bon[0]=pos[0];bon[1]=bon[0]+301;
bon[2]=pos[1];bon[3]=bon[2]+302;

 glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glColor3f(0,0,0);
drawRect(301,302);
glTranslatef(2,289.0,0.0);
drag.dragB(sfont,dcol,ocol,textColor,":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
glTranslatef(283,0.0,0.0);
close.dISTB(icon.XIC);
glPopMatrix();

 glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(4,250.0,0.0);
for (int udt=0;udt<10;udt++){
snprintf(numtext,7,"%d",aline+udt);
numeration[udt].draw(smfont,ocol,numtext);
glTranslatef(0,-25.0,0.0);
}
glPopMatrix();


 glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(38,250.0,0.0);
for (int udt=0;udt<10;udt++){

if(aline+udt<gcode.size()){
memset (&textline[udt],' ',249);
strncpy(textline[udt],gcode[aline+udt].c_str(),249);
}
else{memset (&textline[udt],' ',249);}

uiline[udt].d(sfont,ocol,textline[udt]);
glTranslatef(0,-25.0,0.0);
if(udt>=gcode.size()-1){udt=11;}
}
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(288.0,30.0,0.0f);
gscroll.d(icon);
glPopMatrix();

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glTranslatef(3.0f,3.0f,0.0);
play.dIBKB(icon.PLAYICw);
glTranslatef(25.0f,0.000f,0.0);
pause.dIBKB(icon.PAUSEICw);
 glTranslatef(25.0f,0.000f,0.0);
rev.dISTB(icon.REVERSICw);
   glTranslatef(25.0f,0.000f,0.0);
rew.dISTB(icon.REWINDICw);
  glTranslatef(25.0f,0.000f,0.0);
 rec.dISTB(icon.RECIC);
   glTranslatef(130.0f,0.000f,0.0);
neww.dISTB(icon.NEWICw);
   glTranslatef(25.0f,0.000f,0.0);
op.dISTB(icon.OPENICw);
       glTranslatef(25.0f,0.000f,0.0);
sv.dISTB(icon.SAVEICw);
glPopMatrix();

 }


};


class AXGRF{
float width=300;
float height=50;

char BTXT[7][4];

gline FR;
gline db;
gline temp;

float points[300]={0,20,30,40,50,60,70,80,90,100,20,30,40,50,60,70,80,90,100};
float dbp[300]={0,20,30,40,50,60,70,80,90,100,20,30,40,50,60,70,80,90,100};
float tempp[300]={0,20,30,40,50,60,70,80,90,100,20,30,40,50,60,70,80,90,100};
button drag;
button close;

button more;
button minu;

button FRR;
button FED;
button W;
button dbb;
button S;
button SR;
button tmep;

public:

bool isdragg=false;
bool collision=false;
float bon[4]={0,0,0,0};
float pos[2]={0,0};
double rpos[2]={0,0};

AXGRF(){

snprintf(BTXT[0],4,"fps");
snprintf(BTXT[1],4,"tmp");
snprintf(BTXT[2],4,"rpm");
snprintf(BTXT[3],4,"w/h");
snprintf(BTXT[4],4,"fed");
snprintf(BTXT[5],4,"db");
snprintf(BTXT[6],4,"");

FRR.click=true;
tmep.click=true;
S.click=true;
W.click=true;
FED.click=true;
dbb.click=true;


FR.height=50;
FR.width=300;
FR.color[0]=0.99;FR.color[1]=0.80;FR.color[2]=0.05;
FR.points=points;

db.height=50;
db.width=300;
db.color[0]=0.05;db.color[1]=0.80;db.color[2]=0.99;
db.points=dbp;

temp.height=50;
temp.width=300;
temp.color[0]=0.85;temp.color[1]=0.00;temp.color[2]=0.99;
temp.points=tempp;
}

void u(float variable, float dbv,float tempv){
glDisable(GL_LIGHTING);
FR.u(variable);

db.u(dbv);

temp.u(tempv);
glEnable(GL_LIGHTING);
}



void d(struct ICONST icon,TTF_Font *font,TTF_Font *sfont,SDL_Color textColor,SDL_Color dcol,SDL_Color ocol){
dragpan(drag.click,pos);
if(drag.click){
isdragg=true;}
else{isdragg=false;}

wcolldet(bon,pos);

bon[0]=pos[0];bon[1]=bon[0]+300;
bon[2]=pos[1];bon[3]=bon[2]+100;

glPushMatrix();
glTranslatef(pos[0],pos[1],-1.0f);
glColor3f(0,0,0);
drawRect(300,100);
glTranslatef(2,88.0,0.0);
drag.dragB(sfont,dcol,ocol,textColor,":::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::");
glTranslatef(283,0.0,0.0);
close.dISTB(icon.XIC);
glPopMatrix();


glPushMatrix();
glTranslatef(pos[0],pos[1],-0.7f);
glTranslatef(4,4.0,0.0);
FRR.dTBKB(font,ocol,BTXT[0]);
glTranslatef((FRR.bon[1]-FRR.bon[0])+7,0.0,0.0);
tmep.dTBKB(font,ocol,BTXT[1]);
glTranslatef((tmep.bon[1]-tmep.bon[0])+7,0.0,0.0);
S.dTBKB(font,ocol,BTXT[2]);
glTranslatef((S.bon[1]-S.bon[0])+7,0.0,0.0);
W.dTBKB(font,ocol,BTXT[3]);
glTranslatef((W.bon[1]-W.bon[0])+7,0.0,0.0);
FED.dTBKB(font,ocol,BTXT[4]);
glTranslatef((FED.bon[1]-FED.bon[0])+7,0.0,0.0);
dbb.dTBKB(font,ocol,BTXT[5]);
glTranslatef((dbb.bon[1]-dbb.bon[0])+7,0.0,0.0);
glPopMatrix();

//for(int i=0;i<sizeof(xpoints);i++)xpoints[i]=100*i;
glPushMatrix();
glTranslatef(pos[0],pos[1],-0.8f);
glTranslatef(0,22.0,0.0);
if(FRR.click)FR.d();
if(dbb.click)db.d();
if(tmep.click)temp.d();
glPopMatrix();



 //SDL_Log("line size %d", sizeof(points) / sizeof(points[0]));
}
};


#endif
