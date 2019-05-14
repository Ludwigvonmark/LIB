#ifndef UI_UTILITIES_H_INCLUDED
#define UI_UTILITIES_H_INCLUDED

class TXT{
public:
	float scale = 0.5;

	int W = 150;//Anchura del texto
	int heigth = 150;//Máxima altura permitida
	//int sp = 0;

	int bon[2];//array con los boundaries
        

	TXT() {
	
	}

	~TXT() {
	
	}

	void D(TTF_Font* font, SDL_Color color ,const char* text) {
		SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text, color ,W / scale);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, msg->w, msg->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, msg->pixels);
		bon[0] = msg->w*scale; bon[1] = msg->h*scale;
		//glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, tex);
		glPushMatrix();

		glScalef(scale,scale,scale);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2f(0.0, 0.0);
		glTexCoord2d(1, 1); glVertex2f(msg->w, 0.0);
		glTexCoord2d(1, 0); glVertex2f(msg->w, msg->h);
		glTexCoord2d(0, 0); glVertex2f(0.0, msg->h);

		glEnd();

		glPopMatrix();
		glDeleteTextures(1, &tex);
		//glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		SDL_FreeSurface(msg);
	}

    
    void D(TTF_Font* font, SDL_Color color ,std::string TXT) {
        
        const char* text=TXT.c_str();
        
		SDL_Surface* msg = TTF_RenderText_Blended_Wrapped(font, text, color ,W / scale);
		GLuint tex;
		glGenTextures(1, &tex);
		glBindTexture(GL_TEXTURE_2D, tex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, msg->w, msg->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, msg->pixels);
		bon[0] = msg->w*scale; bon[1] = msg->h*scale;
		//glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, tex);
		glPushMatrix();

		glScalef(scale,scale,scale);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2f(0.0, 0.0);
		glTexCoord2d(1, 1); glVertex2f(msg->w, 0.0);
		glTexCoord2d(1, 0); glVertex2f(msg->w, msg->h);
		glTexCoord2d(0, 0); glVertex2f(0.0, msg->h);

		glEnd();

		glPopMatrix();
		glDeleteTextures(1, &tex);
		//glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		SDL_FreeSurface(msg);
	}
};



class BTN{
	GLfloat mtxpos[16];//Almacena la posición actual recogida de openGL
	bool bk = false;
        
        void UB(){//Updatea la posición y los boundaries del boton
            glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		//bon[1] = bon[0] + im.bon[0]; bon[3] = bon[2] + im.bon[1];//Boundaries de imagen
		bon[1] = bon[0] + tx.bon[0]; bon[3] = bon[2] + tx.bon[1];//Boundaries de texto
        }
        
public:
	IMG im;
	TXT tx;
	float scale = 0.5;
	int bon[4] = { 0,0,0,0 };
        
        int rDrag[2]={0,0};

	bool over = false;
	bool clickl = false;//Click parcial
        bool clickr =false;//Click parcial
        
        bool drag=false;
        
        bool CLICKL=false;//Click completo
        bool CLICKR=false;//Click completo
        
        long nLclicks=0;//Numero de clicks completos en el boton
      
	//bool bkclick = false;
	
	
	void U(int moscx,int moscy, int mosdx,int mosdy, int mosx, int mosy, bool rclick, bool lclick){
            
            
                if(clickl&&over&&!lclick){CLICKL=true;nLclicks++;}
                else {CLICKL=false;}
            
            if ((mosx > bon[0]) && (mosx < bon[1]) && (mosy > bon[2]) && (mosy < bon[3])) {over = true;}
            else { over = false; }
            if (over&&lclick) { clickl = true; } else{clickl=false;}
            //if (lclick&&!over) { clickl = false; }
            
            //Drag rutine
            if(over&&lclick){drag=true;}
            else if(!lclick){drag=false;}
            if(drag){rDrag[0]+=mosx-mosdx;rDrag[1]+=mosy-mosdy;}
            
            
            
        }
        
        void D(TTF_Font* font, SDL_Color color, std::string ms ){
            
            tx.D(font, color, ms);
            UB();
            
        }
        
        void D(SDL_Surface* ico){
            
            
            
        }

	/*void btstyle() {
		if (over) {
			glColor3f(0.4, 0.4, 0.4);
			glPushMatrix(); glTranslatef(bon[1] - bon[0], 0.0, 0.0);
			drawRect(bon[0] - bon[1], -1); glPopMatrix();
		}

		if (click) {
			glColor3f(0.7, 0.9, 0.05);
			glPushMatrix(); glTranslatef(bon[1] - bon[0], 0.0, 0.0);
			drawRect(bon[0] - bon[1], -1); glPopMatrix();
		}
	}


	void stbutt() {
		if ((mosx > bon[0]) && (mosx < bon[1]) && (mosy > bon[2]) && (mosy < bon[3])) {
			over = true;
		}
		else { over = false; }
		if (over&&lclick) { click = true; }
		else { click = false; }

	}

	void bkbutt() {
		bkclick = false;
		if ((mosx > bon[0]) && (mosx < bon[1]) && (mosy > bon[2]) && (mosy < bon[3])) {
			over = true;
		}
		else { over = false; }

		if (!click&&!lclick) { bk = false; }
		else if (click&&!lclick) { bk = true; }

		if (over&&lclick&&!bk) { bkclick = true; click = true; }
		else if (over&&lclick&&bk) { click = false; }
	}

	void swbutt(bool group) {
		if ((mosx > bon[0]) && (mosx < bon[1]) && (mosy > bon[2]) && (mosy < bon[3])) {
			over = true;
		}
		else { over = false; }
		if (over&&lclick) { click = true; }//else{click=false;}
		if (lclick&&!over&&group) { click = false; }
	}

	void dIBKB(SDL_Surface* msg) {
		im.scale = scale;
		im.draw(msg);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + im.bon[0]; bon[3] = bon[2] + im.bon[1];
		bkbutt();
		btstyle();
	}

	void dISTB(SDL_Surface* msg) {
		im.scale = scale;
		im.draw(msg);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + im.bon[0]; bon[3] = bon[2] + im.bon[1];
		stbutt();
		btstyle();
	}

	void dTSWB(TTF_Font* font, SDL_Color color, const char* mnsg, bool group) {
		tx.draw(font, color, mnsg);
		tx.scale = scale;
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + tx.bon[0]; bon[3] = bon[2] + tx.bon[1];
		swbutt(group);
		btstyle();
		//SDL_Log("BUT %dx%dx%dx%d",bon[0],bon[1],bon[2],bon[3]);
		//SDL_Log("MOS %dx%d",mosx,mosy);
	}

	void dTBKB(TTF_Font* font, SDL_Color color, const char* mnsg) {
		tx.draw(font, color, mnsg);
		tx.scale = scale;
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + tx.bon[0]; bon[3] = bon[2] + tx.bon[1];
		bkbutt();
		btstyle();
		//SDL_Log("BUT %dx%dx%dx%d",bon[0],bon[1],bon[2],bon[3]);
		//SDL_Log("MOS %dx%d",mosx,mosy);
	}

	void dTSTB(TTF_Font* font, SDL_Color color, const char* mnsg) {
		tx.draw(font, color, mnsg);
		tx.scale = scale;
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + tx.bon[0]; bon[3] = bon[2] + tx.bon[1];
		stbutt();
		btstyle();
		//SDL_Log("BUT %dx%dx%dx%d",bon[0],bon[1],bon[2],bon[3]);
		//SDL_Log("MOS %dx%d",mosx,mosy);
	}

	void dragB(TTF_Font* font, SDL_Color color, SDL_Color coloro, SDL_Color colorc, const char* mnsg) {
		tx.scale = scale;

		if (over&&!click) {
			tx.draw(font, coloro, mnsg);
		}

		else if (click) {
			tx.draw(font, colorc, mnsg);
		}

		else {
			tx.draw(font, color, mnsg);

		}

		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		bon[0] = mtxpos[12];
		bon[2] = mtxpos[13];
		bon[1] = bon[0] + tx.bon[0]; bon[3] = bon[2] + tx.bon[1];

		if ((mosx > bon[0]) && (mosx < bon[1]) && (mosy > bon[2]) && (mosy < bon[3])) {
			over = true;
		}
		else { over = false; }
		if (over&&lclick) { click = true; }//else{click=false;}
		if (!lclick) { click = false; }

	}*/
};








/*class scroll{
	GLfloat mtxpos[15];

public:
	image down;
	image up;
	image mup;
	image mdw;

	bool click = false;

	int height = 123;
	int siz = 50;
	float scale = 0.5;
	double perc = 0;
	float pos = 0;
	double sensibility = 0.5;

	bool upov = false;
	bool updw = false;

	bool dwov = false;
	bool dwdw = false;

	bool dbov = false;
	bool dbdw = false;

	float Bon[4];

	float dwbut[4];
	float upbut[4];
	float barrbut[4];

	void dd(SDL_Surface* msg) {
		down.scale = scale;
		down.draw(msg);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		dwbut[0] = mtxpos[12];
		dwbut[2] = mtxpos[13];
		dwbut[1] = dwbut[0] + down.bon[0]; dwbut[3] = dwbut[2] + down.bon[1];
	}

	void du(SDL_Surface* msg) {
		up.scale = scale;
		up.draw(msg);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		upbut[0] = mtxpos[12];
		upbut[2] = mtxpos[13];
		upbut[1] = upbut[0] + up.bon[0]; upbut[3] = upbut[2] + up.bon[1];
	}

	void dm(SDL_Surface* msd,SDL_Surface* msu) {

		glPushMatrix();
		glTranslatef(0,pos,0.0);
		mup.scale = scale;
		mup.draw(msd);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		barrbut[0] = mtxpos[12];
		barrbut[2] = mtxpos[13];
		//barrbut[1]=barrbut[0]+mup.bon[0];barrbut[3]=barrbut[2]+mup.bon[1];

		glTranslatef(0.0,siz,0.0);

		mdw.scale = scale;
		mdw.draw(msu);
		glGetFloatv(GL_MODELVIEW_MATRIX, mtxpos);
		barrbut[1] = mtxpos[12] + mdw.bon[0];
		barrbut[3] = mtxpos[13] + mdw.bon[1];

		glPopMatrix();

		glPushMatrix();
		glTranslatef(1.5,pos + 8,0.0);
		glDisable(GL_LIGHTING);
		glBegin(GL_QUADS);
		glColor3f(0.45,0.45,0.45);
		glTexCoord2d(0, 1); glVertex2f(0.0, 0.0);
		glTexCoord2d(1, 1); glVertex2f(7, 0.0);
		glTexCoord2d(1, 0); glVertex2f(7, siz - 8);
		glTexCoord2d(0, 0); glVertex2f(0.0, siz - 8);
		glColor3f(1.0,1.0,1.0);
		glEnd();
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	void clicks() {
		if ((mosx > barrbut[0]) && (mosx < barrbut[1]) && (mosy > barrbut[2]) && (mosy < barrbut[3])) {
			dbov = true;
		}
		else { dbov = false; }
		if (dbov&&lclick) { dbdw = true; }//else{click=false;}
		if (!lclick) { dbdw = false; }

		if ((mosx > upbut[0]) && (mosx < upbut[1]) && (mosy > upbut[2]) && (mosy < upbut[3])) {
			upov = true;
		}
		else { upov = false; }
		if (upov&&lclick) { updw = true; }//else{click=false;}
		if (!lclick) { updw = false; }

		if ((mosx > dwbut[0]) && (mosx < dwbut[1]) && (mosy > dwbut[2]) && (mosy < dwbut[3])) {
			dwov = true;
		}
		else { dwov = false; }
		if (dwov&&lclick) { dwdw = true; }//else{click=false;}
		if (!lclick) { dwdw = false; }
	}

	void sf() {
		clicks();
		if (dbdw) {
			click = true;
			perc -= ((mosy - mosdy)) / (440 * scale);
		}
		else if (dwdw) {
			click = true;
			perc += sensibility;
		}

		else if (updw) {
			click = true;
			perc -= sensibility;
		}

		else {
			click = false;
		}

		//std::cout<<perc<<std::endl;
		if (perc>1) { perc = 1; }
		else if (perc<0) { perc = 0; }

		pos = ((1 - perc)*(height*scale)) + 4;


	}

	void d(struct ICONST icon) {
		sf();

		glPushMatrix();
		dd(icon.SCROLEIC);
		glTranslatef(0.0,height + 24,0.0);
		du(icon.SCROLEIC);
		glPopMatrix();

		glPushMatrix();
		glTranslatef(0.0,pos,0.0);
		dm(icon.SCROLIBIC,icon.SCROLITIC);
		glPopMatrix();
	}
};*/


//Cargador de recursos gráficos

SDL_Surface * AICON(SDL_Surface* ico){

if(ico==NULL){  std::cout<<"UI icon not found"<<std::endl;return NULL;}

SDL_Surface *IC = SDL_ConvertSurfaceFormat(
    ico, SDL_PIXELFORMAT_ABGR8888, 0);


    SDL_FreeSurface(ico);
    return IC;


}

struct ICONST{


//SDL_Surface * axisAPP= IMG_Load("../LIB/GR/RESOURCES/ICONS/AXISAPP.png");
SDL_Surface *APP=AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/MRQS_FCS_APP_LOGO.png"));
//SDL_Surface * axisICO= IMG_Load("../LIB/GR/RESOURCES/ICONS/AXISLOGO.png");
SDL_Surface *ICO=AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/AXISLOGO.png"));

//SDL_Surface * newwIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/NEWw.png");
SDL_Surface * NEWICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/NEWw.png"));
//SDL_Surface * openwIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/OPENw.png");
SDL_Surface * OPENICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/OPENw.png"));
//SDL_Surface * savewIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/SAVEw.png");
SDL_Surface * SAVEICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/SAVEw.png"));

//SDL_Surface * playwIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/PLAYw.png");
SDL_Surface * PLAYICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/PLAYw.png"));
//SDL_Surface * pausewIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/PAUSEw.png");
SDL_Surface * PAUSEICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/PAUSEw.png"));
//SDL_Surface * reverswIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/REVERSw.png");
SDL_Surface * REVERSICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/REVERSw.png"));
//SDL_Surface * rewindwIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/REWINDw.png");
SDL_Surface * REWINDICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/REWINDw.png"));
//SDL_Surface * recIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/REC.png");
SDL_Surface * RECIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/REC.png"));
//SDL_Surface * reloadwIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/RELOADw.png");
SDL_Surface * RELOADICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/RELOADw.png"));

//SDL_Surface * verifIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/VERF.png");
SDL_Surface *VERFIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/VERF.png"));
//SDL_Surface * manualIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/MANUAL.png");
SDL_Surface *MANUALIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/MANUAL.png"));
//SDL_Surface * meIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/-.png");
SDL_Surface *MEIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/-.png"));
//SDL_Surface * resIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/RECOR.png");
SDL_Surface *RESIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/RECOR.png"));
//SDL_Surface * maIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/+.png");
SDL_Surface *MAIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/+.png"));

//SDL_Surface * verifwIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/VERFw.png");
SDL_Surface *VERFICw = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/VERFw.png"));
//SDL_Surface * mewIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/-w.png");
SDL_Surface *MEICw = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/-w.png"));
//SDL_Surface * reswIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/RECORw.png");
SDL_Surface *RESICw = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/RECORw.png"));
//SDL_Surface * rewIC= IMG_Load("../LIB/GR/RESOURCES/ICONS/REw.png");
SDL_Surface * REICw= AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/REw.png"));
//SDL_Surface * mawIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/+w.png");
SDL_Surface *MAICw = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/+w.png"));

//SDL_Surface * moveIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/MOVEw.png");
SDL_Surface *MOVEIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/MOVEw.png"));
//SDL_Surface * opIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/OPw.png");
SDL_Surface *OPIC =AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/OPw.png"));
//SDL_Surface * xIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/Xw.png");
SDL_Surface *XIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/Xw.png"));
//SDL_Surface * ublockIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/UNBLOKw.png");
SDL_Surface *UBLOCKIC = AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/UNBLOKw.png"));
//SDL_Surface * scroleIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLE.png");
SDL_Surface * SCROLEIC =AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLE.png"));
//SDL_Surface * scrolitIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLIT.png");
SDL_Surface * SCROLITIC =AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLIT.png"));
//SDL_Surface * scrolibIC =IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLIB.png");
SDL_Surface * SCROLIBIC =AICON(IMG_Load("../LIB/GR/RESOURCES/ICONS/SCROLIB.png"));
};


#endif
