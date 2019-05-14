#ifndef CAM_H_INCLUDED
#define CAM_H_INCLUDED

class CAM {
public:
	float pos[3] = { 0,0,-300 };
	float target[3] = { 0,0,0 };
	float rx = 45, ry = 45, rz = 0;

	CAM() {

	}

	~CAM() {
	}

	void U(int moscy, int mosdx, int mosdy, int mosx, int mosy,
	bool rclick, bool mclick) {
		pos[2] -= moscy*(pos[2] / 10);

		if (rclick) {
			rx += (mosx - mosdx);
			ry -= (mosdy - mosy);
		}
		if (mclick) {
			pos[0] -= (mosx - mosdx)*(pos[2] / 800);
			pos[1] += (mosdy - mosy)*(pos[2] / 800);
		}

		if (rx>360)rx = 0; if (ry>360)ry = 0; if (rz>360)rz = 0;
		if (rx<0)rx = 360; if (ry<0)ry = 360; if (rz<0)rz = 360;

	}

	void D() {
		glTranslatef(pos[0], pos[1], pos[2]);
		glTranslatef(target[0], target[1], target[2]);
		glRotatef(-ry, 1, 0, 0);
		glRotatef(rx, 0, 0, 1);
		glTranslatef(-target[0], -target[1], -target[2]);
	}
};
#endif
