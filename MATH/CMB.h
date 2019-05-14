#ifndef CMB_H_INCLUDED
#define CMB_H_INCLUDED

//Combinatory algorithms


class BIN_GEN {
	int W = 0; int H = 0;

	int PIX = 0;
	int bpp = 0;

	//std::vector <int> MATRIXDATA;

	int mxpos = 0;
	bool last = false;

public:

	BIN_GEN(int Wv, int Hv) {
		W = Wv; H = Hv;
		PIX = W*H;// total = pow(bpp * 2, PIX);
	//	MATRIXDATA.assign(PIX, 0);
	//	for (int r = 0; r < W; r++) MATRIXDATA[r] = rand() % 2;

	}
	~BIN_GEN() {
	//	MATRIXDATA.clear();
	}

	/*void UMATRIX() {
		mxpos = 0;
		last = true;

		while (last) {

			if (MATRIXDATA[mxpos] == 0) {
				MATRIXDATA[mxpos] = 1;
				for (int e = mxpos - 1; e > 0; e--) { MATRIXDATA[e] = 0; }
				last = false;
			}
			mxpos++;
			if (mxpos >= PIX) {
				mxpos = 0; last = false; for (int rese = 0; rese < PIX; rese++) { MATRIXDATA[rese] = 0; }
			}
			//std::cout << mxpos << "  " <<last<< std::endl;
		}
	}

	std::vector *RMATRIX() {
		return &MATRIXDATA;
	}*/
};


#endif
