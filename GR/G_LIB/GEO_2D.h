#ifndef GEO_2D_H_INCLUDED
#define GEO_2D_H_INCLUDED

void DRect(float sizex, float sizey) {
	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.0);
	glVertex2f(sizex, 0.0);
	glVertex2f(sizex, sizey);
	glVertex2f(0.0, sizey);
	glColor3f(1.0, 1.0, 1.0);
	glEnd();
}

class MATRIX_2D {
	int W = 0; int H = 0;

	int PIX = 0;
	int bpp = 0;

	std::vector <int> MATRIXDATA;

	int mxpos = 0;
	bool last = false;


public:

	//UINT64 state = 0;
	//UINT64 total = 0;

	//UINT64 cicles = 0;

	MATRIX_2D (int Wv, int Hv, int bppv){
		W = Wv; H = Hv; bpp = bppv;
		PIX = W*H;// total = pow(bpp * 2, PIX);
		MATRIXDATA.assign(PIX*bpp,0);
		for (int r = 0; r < W;r++) MATRIXDATA[r] = rand() % 2;

	}
	~MATRIX_2D() {
		MATRIXDATA.clear();
	}

	/*void UMATIX() {

			for (int s = 1; s < (PIX*bpp) - 1; s++) {
				if (state % s == 0)MATRIXDATA[s] = 1;
				else MATRIXDATA[s] = 0;

			}

			state++; 
			//std::cout << state << "  " << total << "  " << cicles<< std::endl;
			if (state >= (pow(bpp * 2, PIX))) { state = 0; cicles++; }
		}*/

	void UMATRIX_pro() {
		mxpos = 0;
		last = true;

		while (last) {

			if (MATRIXDATA[mxpos] == 0) {
				MATRIXDATA[mxpos] = 1;
				for (int e = mxpos-1; e > 0; e--) { MATRIXDATA[e] = 0; }
				last = false;
			}
			mxpos++;
			if (mxpos >= PIX) { mxpos = 0; last = false; for (int rese = 0; rese < PIX; rese++) { MATRIXDATA[rese] = 0; }
			}
			//std::cout << mxpos << "  " <<last<< std::endl;
		}
	}
	

	void DMATRIX() {
		glBegin(GL_POINTS);
		glPointSize(0.5);
		//glLineWidth(2);
		//glVertex2f(0.0, 0.0);
		for (int y = 0; y < H; y++) {		
		for (int x = 0; x < W; x++) {
			glColor3f(GLfloat(MATRIXDATA[(x+(y*H))]), GLfloat(MATRIXDATA[(x + (y*H))]), GLfloat(MATRIXDATA[(x + (y*H))]));
			//glColor3f(y, x, x*y);
			glVertex2f(x, y);
		}
		}
		//glVertex2f(H, W);
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
	}
};






	//	glDisableVertexAttribArray(attribute_coord2d);
	//	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//}
//};*/

#endif
