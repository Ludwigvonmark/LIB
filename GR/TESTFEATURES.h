#ifndef TESTFEATURES_H_INCLUDED
#define TESTFEATURES_H_INCLUDED



class D2_GRAFIC {
	

public:
	int imgw = 400;
	int imgh = 400;
	int channels = 4;
	int bon[2];
	UINT8 pxData[400 * 400 * 4];

	std::vector <UINT8> MATRIXDATA;
	//std::vector <UINT8> MATRIXDATA;

	D2_GRAFIC() {
		//memset(pxData, 'w', (400 *400 * 4)-1);

		//W = Wv; H = Hv; bpp = bppv;
		//PIX = W*H;// total = pow(bpp * 2, PIX);
		MATRIXDATA.assign(400 * 400 * 4, 0);
		for (int r = 3; r < (400 * 400*4); r+=4)MATRIXDATA[r] = 255;//A
		//for (int r = 4; r < (400 * 400 * 4) ; r += 4)MATRIXDATA[r] = 200 * (rand() % 2);//R
		//for (int r = 5; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 200 * (rand() % 2);//G
		for (int r = 6; r < (400 * 400 * 4) ; r += 4)MATRIXDATA[r] = 200 * (rand() % 2);//B

		//for (int r = 4; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 255;//R
		//for (int r = 5; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 255;//G
		//for (int r = 6; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 255;//B

		for (int r = 0; r < (400 * 400 * 4) - 1; r++)pxData[r] = MATRIXDATA[r];
//		memcpy(pxData, MATRIXDATA,( 400 * 400 * 4)-10);
	}

	void UP_2D() {
		for (int r = 3; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 255;//A
															
		for (int r = 6; r < (400 * 400 * 4); r += 4)MATRIXDATA[r] = 200 * (rand() % 2);//B

		for (int r = 0; r < (400 * 400 * 4) - 1; r++)pxData[r] = MATRIXDATA[r];
	}

	void DR_2D() {
		Uint32 rmask, gmask, bmask, amask;
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
#endif


		//SDL_Surface* D2_SURF = SDL_CreateRGBSurfaceFrom(&MATRIXDATA,    
		SDL_Surface* D2_SURF = SDL_CreateRGBSurfaceFrom((void*)pxData,
			400,
			400,
			channels * 8,          // bits per pixel = 24
			400 * channels,  // pitch
			rmask,
			gmask,
			bmask,
			amask);                    // alpha mask (none)

		if (D2_SURF == NULL) {
			fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
			exit(1);
		}

		GLuint d2gtex;
	
		float scale = 0.5;
		
		glGenTextures(1, &d2gtex);
		glBindTexture(GL_TEXTURE_2D, d2gtex);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, D2_SURF->w, D2_SURF->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, D2_SURF->pixels);
		bon[0] = D2_SURF->w*scale; bon[1] = D2_SURF->h*scale;

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, d2gtex);


		glScalef(scale, scale, scale);
		glBegin(GL_QUADS);
		glTexCoord2d(0, 1); glVertex2f(0.0, 0.0);
		glTexCoord2d(1, 1); glVertex2f(D2_SURF->w, 0.0);
		glTexCoord2d(1, 0); glVertex2f(D2_SURF->w, D2_SURF->h);
		glTexCoord2d(0, 0); glVertex2f(0.0, D2_SURF->h);

		glEnd();

		glDeleteTextures(1, &d2gtex);
		glDisable(GL_BLEND);
		SDL_FreeSurface(D2_SURF);
	}


};
#endif