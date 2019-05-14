#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class timer {
	Uint32 ticks;
	Uint32 start;

	Uint32 frames;
	Uint32 framee;


public:
	Uint32 frame;
	Uint32 framerate;
	Uint32 elapse;

	void get() {
		ticks = SDL_GetTicks();
		frame++;
		if (ticks>2147480000) { ticks = 0; }
		if (frame>2147480000) { frame = 0; }
	}

	void getframerate() {

		if (frame>1) {
			framee = ticks - frames;
			frames = ticks;
			frame = 0;
		}
		framerate = framee;
	}

	void startt() {
		start = ticks;
	}

	float stopt() {
		elapse = ticks - start;
		return elapse;
	}
};



#endif