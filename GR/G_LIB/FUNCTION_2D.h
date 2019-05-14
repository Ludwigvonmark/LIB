#ifndef FUNCTION_2D_H_INCLUDED
#define FUNCTION_2D_H_INCLUDED

class function2D{

	float maximun;
float minimun;
float rel;

int ndata = 300;
float var;

public:
	int width = 300;
	float height = 50;
	float *points;
	float color[3];

	function2D() {
		points = new float[width];
	}

	~function2D() {
		delete[] points;
	}

	void u(float variable) {
		maximun = 0;
		minimun = 80;
		var = variable;
		if (ndata>0)ndata--; else {}
		points[299] = var;
		for (int i = 0; i<300; i++) {
			points[i] = points[i + 1];
			if (points[i]>maximun) { maximun = points[i]; rel = height / maximun; }
			if (points[i]<minimun) { minimun = points[i]; }
			//points[i]=height/points[i];points[i]=points[i]/rel;
			//points[i]=((height/points[i])/height)*1000;
		}

	}

	void d() {

		glLineWidth(1);
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_LINES);

		//for(int i=0;i<sizeof(ypoints);i+=width/sizeof(ypoints)){
		for (int i = 1; i<299; i++) {
			if (points[i] == 0) {}
			else {
				glVertex3f(i, (points[i])*rel, 0.0);
				glVertex3f(i + 1, (points[i - 1])*rel, 0.0);
			}

		}

		glEnd();
	}
};


#endif