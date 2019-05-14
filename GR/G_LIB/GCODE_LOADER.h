#ifndef GCODE_LOADER_H_INCLUDED
#define GCODE_LOADER_H_INCLUDED





char dat[10];
char idt[1];

float GETGDS(std::string id, char* in) {
	float result;

	std::stringstream inst;
	inst << in;
	while (inst) {
		std::string a;
		inst >> a;
		if (a.compare(0, 1, id) == 0) {
			a.erase(0, 1);
			strcpy(dat, a.c_str());
			result = strtod(dat, 0);

			return result;
		}
	}
}

float GETGDR(std::string id, char* in, float cur) {

	float result;
	std::stringstream inst;
	inst << in;
	while (inst) {
		std::string a;
		inst >> a;
		if (a.compare(0, 1, id) == 0) {
			a.erase(0, 1);
			strcpy(dat, a.c_str());
			result = strtod(dat, 0);

			return result;
		}
	}return cur;
}


bool GETC(std::string cmd, char* in) {
	std::stringstream inst;
	inst << in;
	while (inst) {
		std::string a;
		inst >> a;
		if (a.compare(cmd) == 0)return true;
		else return false;
	}
}


const char *ADDGDS(char* current, std::string id, float data) {

	strcpy(idt, id.c_str());
	bool exist = false;
	std::stringstream in;
	in << current;
	std::stringstream out;
	while (in) {
		std::string a;
		in >> a;
		if (a.compare(0, 1, id) == 0) {
			exist = true;
			a.clear();
			int c = snprintf(dat, 10, "%s%f", idt, data);
			out << dat << " ";
		}
		else { out << a << " "; }
	}
	if (!exist) {
		int c = snprintf(dat, 10, "%s%f", idt, data);
		out << dat << " ";
	}
	const std::string tmp = out.str();
	return tmp.c_str();

}






class gpath {
	int gcid;
	//float path [];
	double xi, yi, zi;

	std::stringstream pathss;
	std::string gline;


public:
	int cline;
	int ccline;

	gpath() {
		xi = 0; yi = 0; zi = 0;
		gcid = glGenLists(1);
		//glEndList();
	}

	~gpath() {

	}
	void u(char* gcode) {
		//std::ifstream axgtem("AXG.ngc");

		pathss << gcode;

		glNewList(gcid, GL_COMPILE);
		glLineWidth(1);
		glColor3f(0.91, 0.41, 0.1);
		glBegin(GL_LINES);

		while (std::getline(pathss, gline)) {

			//std::cout<<gline<<'\n';

			std::stringstream instruction;
			instruction << gline;
			glVertex3f(xi, yi, zi);


			while (instruction) {


				std::string att;
				instruction >> att;
				// std::cout<<att<<'\n';

				if (att.compare("G0") == 0) {
					glColor3f(0.1, 0.81, 0.1);
				}
				if (att.compare("G1") == 0) {
					glColor3f(0.91, 0.41, 0.1);

				}

				if (att.compare(0, 1, "X") == 0) {
					att.erase(0, 1);
					char in[15];
					strcpy(in, att.c_str());
					xi = strtod(in, 0);
				}
				if (att.compare(0, 1, "Y") == 0) {
					att.erase(0, 1);
					char in[15];
					strcpy(in, att.c_str());
					yi = strtod(in, 0);
				}


				if (att.compare(0, 1, "Z") == 0) {
					att.erase(0, 1);
					char in[15];
					strcpy(in, att.c_str());
					zi = strtod(in, 0);
				}


			}
			glVertex3f(xi, yi, zi);
		}
		glEnd();
		glColor3f(1.0, 1.0, 1.0);
		glEndList();
	}

	void d() {
		glCallList(gcid);

	}

};
#endif