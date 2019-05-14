#ifndef VBO_H_INCLUDED
#define VBO_H_INCLUDED

class VBO {
	
public:

	unsigned int vbo, ind;   //indicis





	VBO() {
		float f[] = { 0,2,-4,1,0,0,-2,-2,-4,0,1,0,2,-2,-4,0,0,1 };	 //vertex array (3 component vertex, 3 component color)
		unsigned int indarr[] = { 0,1,2 };
		glClearColor(0, 0, 0, 1);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(50, 640.0 / 480.0, 1, 1000);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);

		glGenBuffers(1, &vbo);   //generate an index for the vertexbuffer
		glGenBuffers(1, &ind);   //and the indices

		glBindBuffer(GL_ARRAY_BUFFER, vbo);      //use vbo as ARRAY_BUFFER
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind);      //use ind as ELEMENT_ARRAY_BUFFER (index-array)
		glBufferData(GL_ARRAY_BUFFER, sizeof(f), f, GL_STATIC_DRAW);//fill up the array with vertex and color-data
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indarr), indarr, GL_STATIC_DRAW);//this one with indicis
	}

	~VBO() {
		glDeleteBuffers(1, &ind);        //delete it
		glDeleteBuffers(1, &vbo);
	}



void D_VBO() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);      //use this VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind);      //and index
	glEnableClientState(GL_VERTEX_ARRAY);   //we use vertex and
	glEnableClientState(GL_COLOR_ARRAY);    //color data
											//the vertex has 3 component (x,y,z),it has the type float, 3 float is the vertex + 3 float is the color/6*sizeof(float), and the first
											//coordinate start at the begginning of the VBO
	glVertexPointer(3, GL_FLOAT, 6 * sizeof(float), 0);
	//same thing
	glColorPointer(3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);               //draw it
	glDisableClientState(GL_COLOR_ARRAY);   //disable everything
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};

#endif