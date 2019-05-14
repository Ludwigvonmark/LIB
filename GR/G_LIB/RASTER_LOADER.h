#ifndef RASTER_LOADER_H_INCLUDED
#define RASTER_LOADER_H_INCLUDED


class IMG {
public:
	float scale = 0.5;
	int bon[2];

	void D(SDL_Surface* msg) {
		GLuint img;
		glGenTextures(1, &img);
		glBindTexture(GL_TEXTURE_2D, img);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, msg->w, msg->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, msg->pixels);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glDisable(GL_LIGHTING);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glPushMatrix();
		glScalef(scale, scale, scale);
		glBegin(GL_QUADS);

		glTexCoord2d(0, 1); glVertex2f(0.0, 0.0);
		glTexCoord2d(1, 1); glVertex2f(msg->w, 0.0);
		glTexCoord2d(1, 0); glVertex2f(msg->w, msg->h);
		glTexCoord2d(0, 0); glVertex2f(0.0, msg->h);
		bon[0] = msg->w*scale; bon[1] = msg->h*scale;
		glEnd();

		glPopMatrix();
		glDeleteTextures(1, &img);
		glEnable(GL_LIGHTING);
		glDisable(GL_BLEND);
		//SDL_FreeSurface( msg );
	}
};


#endif
