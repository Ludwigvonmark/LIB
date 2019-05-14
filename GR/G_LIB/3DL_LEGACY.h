#ifndef AX3DL_H_INCLUDED
#define AX3DL_H_INCLUDED

class TDSCEN{
struct aiLogStream stream;
const struct aiScene* scene = NULL;
GLuint scene_list = 0;
 aiVector3D scene_min, scene_max, scene_center;

// current rotation angle
static float angle;

public:

TDSCEN(){


#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)
}
// ----------------------------------------------------------------------------
void reshape(int width, int height)
{
	const double aspectRatio = (float) width / height, fieldOfView = 45.0;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, aspectRatio,
		1.0, 1000.0);  /* Znear and Zfar */
	glViewport(0, 0, width, height);
}

// ----------------------------------------------------------------------------
void get_bounding_box_for_node (const struct aiNode* nd,
	 aiVector3D* min,
	 aiVector3D* max,
	 aiMatrix4x4* trafo
){
    aiMatrix4x4 prev;
	unsigned int n = 0, t;

	prev = *trafo;
	aiMultiplyMatrix4(trafo,&nd->mTransformation);

	for (n; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (t = 0; t < mesh->mNumVertices; ++t) {

			aiVector3D tmp = mesh->mVertices[t];
			aiTransformVecByMatrix4(&tmp,trafo);

			min->x = aisgl_min(min->x,tmp.x);
			min->y = aisgl_min(min->y,tmp.y);
			min->z = aisgl_min(min->z,tmp.z);

			max->x = aisgl_max(max->x,tmp.x);
			max->y = aisgl_max(max->y,tmp.y);
			max->z = aisgl_max(max->z,tmp.z);
		}
	}

	for (n = 0; n < nd->mNumChildren; ++n) {
		get_bounding_box_for_node(nd->mChildren[n],min,max,trafo);
	}
	*trafo = prev;
}

// ----------------------------------------------------------------------------
void get_bounding_box ( aiVector3D* min,  aiVector3D* max)
{
	aiMatrix4x4 trafo;
	aiIdentityMatrix4(&trafo);

	min->x = min->y = min->z =  1e10f;
	max->x = max->y = max->z = -1e10f;
	get_bounding_box_for_node(scene->mRootNode,min,max,&trafo);
}

// ----------------------------------------------------------------------------
void color4_to_float4(const  aiColor4D *c, float f[4])
{
	f[0] = c->r;
	f[1] = c->g;
	f[2] = c->b;
	f[3] = c->a;
}

// ----------------------------------------------------------------------------
void set_float4(float f[4], float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

// ----------------------------------------------------------------------------
void apply_material(const struct aiMaterial *mtl)
{
	float c[4];

	GLenum fill_mode;
	int ret1, ret2;
	 aiColor4D diffuse;
	 aiColor4D specular;
	 aiColor4D ambient;
	 aiColor4D emission;
	float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;

	set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
		color4_to_float4(&diffuse, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
		color4_to_float4(&specular, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

	set_float4(c, 0.2f, 0.2f, 0.2f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
		color4_to_float4(&ambient, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

	set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
	if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
		color4_to_float4(&emission, c);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

	max = 1;
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if(ret1 == AI_SUCCESS) {
    	max = 1;
    	ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if(ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
        	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
}
// ----------------------------------------------------------------------------
void recursive_render (const struct aiScene *sc, const struct aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {

				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

// ----------------------------------------------------------------------------

int loadasset (const char* path)
{
	// we are taking one of the postprocessing presets to avoid
	// spelling out 20+ single postprocessing flags here.

	scene = aiImportFile(path,aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene) {
		get_bounding_box(&scene_min,&scene_max);
		scene_center.x = (scene_min.x + scene_max.x) / 2.0f;
		scene_center.y = (scene_min.y + scene_max.y) / 2.0f;
		scene_center.z = (scene_min.z + scene_max.z) / 2.0f;
		return 0;
	}
	return 1;
}

// ----------------------------------------------------------------------------
void TDI(const char* path)
{
	float tmp;
if( 0 != loadasset(path) ){

			//return -1;
		}

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

	// rotate it around the y axis
	//glRotatef(angle,0.f,1.f,0.f);

	// scale the whole asset to fit into our view frustum
	tmp = scene_max.x-scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
	tmp = 1.f / tmp;
	//glScalef(tmp, tmp, tmp);

        // center the model
	glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

        // if the display list has not been made yet, create a new one and
        // fill it with scene contents
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.
	    recursive_render(scene, scene->mRootNode);
	    glEndList();
	}

	//glCallList(scene_list);




}

// ----------------------------------------------------------------------------



void TDD(){
glCallList(scene_list);
}

};




class MODEL{

};






















/*

class vector3d{
	public:
		float x,y,z;
vector3d(){
	x=y=z=0;}
vector3d(float a,float b){
	x=a;	y=b;	z=0;}
vector3d(float a,float b,float c){
	x=a;	y=b;	z=c;}

float dotProduct(const vector3d& vec2){
	return (x*vec2.x+y*vec2.y+z*vec2.z);}
vector3d crossProduct(const vector3d& vec2){
	return vector3d();}

float length(){
	return sqrt(x*x+y*y+z*z);}
void normalize(){
	float len=length();
	if(len!=0)	{
		x/=len;		y/=len;		z/=len;	}
}

void change(float a,float b,float c){
	x=a;	y=b;	z=c;}

void change(vector3d vec2){
	x=vec2.x;	y=vec2.y;	z=vec2.z;}
void changeX(float a){
	x=a;}
void changeY(float a){
	y=a;}
void changeZ(float a){
	z=a;}

vector3d operator+(const vector3d& vec2){
	return vector3d(x+vec2.x,y+vec2.y,z+vec2.z);}
vector3d operator-(const vector3d& vec2){
	return vector3d(x-vec2.x,y-vec2.y,z-vec2.z);}

vector3d operator*(float num){
	return vector3d(x*num,y*num,z*num);}

vector3d operator/(float num){
	if(num!=0)	return vector3d(x/num,y/num,z/num);
	else	return vector3d();
}

vector3d& operator+=(const vector3d& vec2){
	x+=vec2.x;	y+=vec2.y;	z+=vec2.z;	return *this;}
vector3d& operator-=(const vector3d& vec2){
	x-=vec2.x;	y-=vec2.y;	z-=vec2.z;	return *this;}
vector3d& operator*=(float num){
	x*=num;	y*=num;	z*=num;	return *this;}
vector3d& operator/=(float num){
	if(num!=0)	{
		x/=num;		y/=num;		z/=num;	}
	return *this;}


bool operator==(const vector3d vec2){
	return (x==vec2.x && y==vec2.y && z==vec2.z);}

bool operator!=(const vector3d vec2){
	!(*this==vec2);}

friend std::ostream& operator<<(std::ostream& out,const vector3d& vec){
	out << vec.x << " " << vec.y << " " << vec.z << std::endl;
	return out;}
};

struct vertexData{
	vector3d position;
	vector3d normal;
	vector3d tangent;
	vector3d color;
	float U,V;
};

struct textureData{
	unsigned int id;
	unsigned int type;
};

class mesh{
	std::vector<vertexData> data;
	std::vector<textureData> textures;
	std::vector<unsigned int> indices;
	unsigned int VBO;
	unsigned int IND;
	public:
		mesh(std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<textureData>* td){
	data=*vd;
	indices=*id;
	if(td) textures=*td;

	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,data.size()*sizeof(vertexData),
	&data[0],GL_STATIC_DRAW);


	glGenBuffers(1,&IND);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int),&indices[0],GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

}
		~mesh(){
	glDeleteBuffers(1,&VBO);
	glDeleteBuffers(1,&IND);
}

void draw(unsigned int programId){
	//attribute vec3 vertex
	int vertex=glGetAttribLocation(programId,"vertex"); //0
	int normal=glGetAttribLocation(programId,"normal"); //1
	int tangent=glGetAttribLocation(programId,"tangent"); //2
	int color=glGetAttribLocation(programId,"color"); //3
	int UV=glGetAttribLocation(programId,"UV"); //4

	//texture0
	//texture1...
	std::string str="texture";
	for(int i=0;i<textures.size();i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D,textures[i].id);
		glUniform1i(glGetUniformLocation(programId,(str+(char)(i+'0')).c_str()),i);
	}

	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),0);

	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(3*sizeof(float)));

	glEnableVertexAttribArray(tangent);
	glVertexAttribPointer(tangent,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(6*sizeof(float)));

	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color,3,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(9*sizeof(float)));

	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV,2,GL_FLOAT,GL_FALSE,sizeof(vertexData),(void*)(12*sizeof(float)));

	glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);

	glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(tangent);
	glDisableVertexAttribArray(color);
	glDisableVertexAttribArray(UV);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

};


class meshLoader{
	std::vector<mesh*> meshes;
	void recursiveProcess(aiNode* node,const aiScene* scene){
	//process
	for(int i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* meshV=scene->mMeshes[node->mMeshes[i]];
		processMesh(meshV,scene);
	}
	//recursion
	for(int i=0;i<node->mNumChildren;i++)
	{
		recursiveProcess(node->mChildren[i],scene);
	}
}
	void processMesh(aiMesh* meshV,const aiScene* scene){
	std::vector<vertexData> data;
	std::vector<unsigned int> indices;
	std::vector<textureData> textures;
	aiColor4D col;
	aiMaterial* mat=scene->mMaterials[meshV->mMaterialIndex];
	aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);
	vector3d defaultColor(col.r,col.g,col.b);

	for(int i=0;i<meshV->mNumVertices;i++)	{
			vertexData tmp;
			vector3d tmpVec;

			//position
			tmpVec.x=meshV->mVertices[i].x;
			tmpVec.y=meshV->mVertices[i].y;
			tmpVec.z=meshV->mVertices[i].z;
			tmp.position=tmpVec;
            SDL_Log("VERTICES %f %f %f", tmpVec.x,tmpVec.y,tmpVec.z);
			//normals
			tmpVec.x=meshV->mNormals[i].x;
			tmpVec.y=meshV->mNormals[i].y;
			tmpVec.z=meshV->mNormals[i].z;
			tmp.normal=tmpVec;


			//tangent
			if(meshV->mTangents)			{
				tmpVec.x=meshV->mTangents[i].x;
				tmpVec.y=meshV->mTangents[i].y;
				tmpVec.z=meshV->mTangents[i].z;
			}else{
				tmpVec.x=1.0;
				tmpVec.y=tmpVec.z=0;
			}
			tmp.tangent=tmpVec;


			//colors
			if(meshV->mColors[0])			{
				//!= material color
				tmpVec.x=meshV->mColors[0][i].r;
				tmpVec.y=meshV->mColors[0][i].g;
				tmpVec.z=meshV->mColors[0][i].b;

			}else{
				tmpVec=defaultColor;
			}
			tmp.color=tmpVec;

			//color
			if(meshV->mTextureCoords[0])			{
				tmpVec.x=meshV->mTextureCoords[0][i].x;
				tmpVec.y=meshV->mTextureCoords[0][i].y;
			}else{
				tmpVec.x=tmpVec.y=tmpVec.z=0.0;
			}
			tmp.U=tmpVec.x;
			tmp.V=tmpVec.y;
			data.push_back(tmp);
	}

	for(int i=0;i<meshV->mNumFaces;i++)	{
		aiFace face=meshV->mFaces[i];
		for(int j=0;j<face.mNumIndices;j++) //0..2
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++)	{
		aiString str;
		mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
		textureData tmp;
		tmp.id=loadTexture(str.C_Str());
		tmp.type=0;
		textures.push_back(tmp);
	}
	meshes.push_back(new mesh(&data,&indices,&textures));
}

	unsigned int loadTexture(const char* filename)
{
	unsigned int num;
	glGenTextures(1,&num);
	SDL_Surface* img=IMG_Load(filename);
	if(img==NULL)
	{
		//std::cout << "img was not loaded" << std::endl;
		return -1;
	}

	//SDL_PixelFormat form={NULL,32,4,0,0,0,0,0,0,0,0,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2=SDL_ConvertSurface(img,img->format,SDL_SWSURFACE);
	//SDL_Surface *img2 = SDL_ConvertSurfaceFormat(
    //img, SDL_PIXELFORMAT_ARGB8888,SDL_SWSURFACE);

	if(img2==NULL)
	{
		std::cout << "img2 was not loaded" << std::endl;
	return -1;
	}
	glBindTexture(GL_TEXTURE_2D,num);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return num;
}

	public:
		meshLoader(const char* filenameV)
{
	Assimp::Importer importer;

	const aiScene* sceneV=importer.ReadFile(filenameV, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	if(sceneV->mFlags==AI_SCENE_FLAGS_INCOMPLETE || !sceneV->mRootNode)	{

		std::cout << "The file wasn't successfuly opened " << filenameV << std::endl;
		return;
	}

	recursiveProcess(sceneV->mRootNode,sceneV);

}

		~meshLoader(){
	for(int i=0;i<meshes.size();i++)
		delete meshes[i];
}
		void draw(unsigned int programId){
	for(int i=0;i<meshes.size();i++)
		meshes[i]->draw(programId);
}
		std::vector<mesh*>& getMeshes(){
	return meshes;
}
};





meshLoader* scene;
//data->vertex->fragment

void loadFile(const char* fn,std::string& str)
{
	std::ifstream in(fn);
	if(!in.is_open())
	{
		std::cout << "The file " << fn << " cannot be opened\n";
		return;
	}
	char tmp[300];
	while(!in.eof())
	{
		in.getline(tmp,300);
		str+=tmp;
		str+='\n';
	}
}

unsigned int loadShader(std::string& source,unsigned int mode)
{
	unsigned int id;
	id=glCreateShader(mode);

	const char* csource=source.c_str();

	glShaderSource(id,1,&csource,NULL);
	glCompileShader(id);
	char error[1000];
	glGetShaderInfoLog(id,1000,NULL,error);
	std::cout << "Compile status: \n" << error << std::endl;
	return id;
}

unsigned int vs,fs,program;

void initShader(const char* vname,const char* fname)
{
	std::string source;
	loadFile(vname,source);
	vs=(source,GL_VERTEX_SHADER);
	source="";
	loadFile(fname,source);
	fs=loadShader(source,GL_FRAGMENT_SHADER);

	program=glCreateProgram();
	glAttachShader(program,vs);
	glAttachShader(program,fs);

	glLinkProgram(program);
	glUseProgram(program);
}

void clean()
{
	glDetachShader(program,vs);
	glDetachShader(program,fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}

void init()
{

	initShader("AX3D/vertex.vs","AX3D/fragment.frag");
	scene=new meshLoader("AX3D/test.blend");
}

void display()
{
float lpos[]={-1.0,3.7,-2.0,1.0};
glLightfv(GL_LIGHT0,GL_POSITION,lpos);

glTranslated(0.0,-1.0,-5.0);



glLoadIdentity();
glTranslated(0.0,0.0,-12.0);

glColor3f(0.05,0.05,0.05);


glColor3f(1.0,1.0,1.0);

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	gluPerspective(50,SCREEN_WIDTH/SCREEN_HEIGHT,1,1000);
	//cam.Control();
	//cam.UpdateCamera();

	glUniform3f(glGetUniformLocation(program,"lightPos"),0,1,2);
	//glUniform3f(glGetUniformLocation(program,"cameraPosition"),cam.getLocation().x,cam.getLocation().y,cam.getLocation().z);
	scene->draw(program);

}*/






/*
struct coordinate{
        float x,y,z;
        coordinate(float a,float b,float c) : x(a),y(b),z(c) {};
};



struct face{
        int facenum;
        bool four;
        int faces[4];
        face(int facen,int f1,int f2,int f3) : facenum(facen){  //constructor for triangle
                faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                four=false;
        }
        face(int facen,int f1,int f2,int f3,int f4) : facenum(facen){ //overloaded constructor for quad
                faces[0]=f1;
                faces[1]=f2;
                faces[2]=f3;
                faces[3]=f4;
                four=true;
        }
};



int loadObject(const char* filename)
{
        std::vector<std::string*> coord;        //read every single line of the obj file as a string
        std::vector<coordinate*> vertex;
        std::vector<face*> faces;
        std::vector<coordinate*> normals;       //normal vectors for every face
        std::ifstream in(filename);     //open the .obj file
        if(!in.is_open())       //if not opened, exit with -1
        {
                std::cout << "Nor oepened" << std::endl;
                return -1;
        }
        char buf[256];
        //read in every line to coord
        while(!in.eof())
        {
                in.getline(buf,256);
                coord.push_back(new std::string(buf));
        }
        //go through all of the elements of coord, and decide what kind of element is that
        for(int i=0;i<coord.size();i++)
        {
                if(coord[i]->c_str()[0]=='#')   //if it is a comment (the first character is #)
                        continue;       //we don't care about that
                else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]==' ') //if vector
                {
                        float tmpx,tmpy,tmpz;
                        sscanf(coord[i]->c_str(),"v %f %f %f",&tmpx,&tmpy,&tmpz);       //read in the 3 float coordinate to tmpx,tmpy,tmpz
                        vertex.push_back(new coordinate(tmpx,tmpy,tmpz));       //and then add it to the end of our vertex list
                }else if(coord[i]->c_str()[0]=='v' && coord[i]->c_str()[1]=='n')        //if normal vector
                {
                        float tmpx,tmpy,tmpz;   //do the same thing
                        sscanf(coord[i]->c_str(),"vn %f %f %f",&tmpx,&tmpy,&tmpz);
                        normals.push_back(new coordinate(tmpx,tmpy,tmpz));
                }else if(coord[i]->c_str()[0]=='f')     //if face
                {
                        int a,b,c,d,e;
                        if(count(coord[i]->begin(),coord[i]->end(),' ')==3)     //if it is a triangle (it has 3 space in it)
                        {
                  sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b);
                                faces.push_back(new face(b,a,c,d));     //read in, and add to the end of the face list
                        }else{
                                sscanf(coord[i]->c_str(),"f %d//%d %d//%d %d//%d %d//%d",&a,&b,&c,&b,&d,&b,&e,&b);
                                faces.push_back(new face(b,a,c,d,e));   //do the same, except we call another constructor, and we use different pattern
                        }
                }
        }
//raw
        int num;        //the id for the list
        num=glGenLists(1);      //generate a uniqe
        glNewList(num,GL_COMPILE);      //and create it
        for(int i=0;i<faces.size();i++)
        {
                if(faces[i]->four)      //if it's a quad draw a quad
                {
                        glBegin(GL_QUADS);
                                //basically all I do here, is use the facenum (so the number of the face) as an index for the normal, so the 1st normal owe to the first face
                                //I subtract 1 because the index start from 0 in C++
                                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                                //draw the faces
                                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[3]-1]->x,vertex[faces[i]->faces[3]-1]->y,vertex[faces[i]->faces[3]-1]->z);
                        glEnd();
                }else{
                        glBegin(GL_TRIANGLES);
                                glNormal3f(normals[faces[i]->facenum-1]->x,normals[faces[i]->facenum-1]->y,normals[faces[i]->facenum-1]->z);
                                glVertex3f(vertex[faces[i]->faces[0]-1]->x,vertex[faces[i]->faces[0]-1]->y,vertex[faces[i]->faces[0]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[1]-1]->x,vertex[faces[i]->faces[1]-1]->y,vertex[faces[i]->faces[1]-1]->z);
                                glVertex3f(vertex[faces[i]->faces[2]-1]->x,vertex[faces[i]->faces[2]-1]->y,vertex[faces[i]->faces[2]-1]->z);
                        glEnd();
                }
        }
        glEndList();
        //delete everything to avoid memory leaks
        for(int i=0;i<coord.size();i++)
                delete coord[i];
        for(int i=0;i<faces.size();i++)
                delete faces[i];
        for(int i=0;i<normals.size();i++)
                delete normals[i];
        for(int i=0;i<vertex.size();i++)
                delete vertex[i];
        return num;     //return with the id
}



unsigned int loadTexture(const char* filename)
{
        SDL_Surface* img = SDL_LoadBMP(filename);
        unsigned int id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        SDL_FreeSurface(img);
        return id;
}*/




/*
class vector3d{
	public:
		float x,y,z;
vector3d(){
	x=y=z=0;}
vector3d(float a,float b){
	x=a;	y=b;	z=0;}
vector3d(float a,float b,float c){
	x=a;	y=b;	z=c;}

float dotProduct(const vector3d& vec2){
	return (x*vec2.x+y*vec2.y+z*vec2.z);}
vector3d crossProduct(const vector3d& vec2){
	return vector3d();}

float length(){
	return sqrt(x*x+y*y+z*z);}
void normalize(){
	float len=length();
	if(len!=0)	{
		x/=len;		y/=len;		z/=len;	}
}

void change(float a,float b,float c){
	x=a;	y=b;	z=c;}

void change(vector3d vec2){
	x=vec2.x;	y=vec2.y;	z=vec2.z;}
void changeX(float a){
	x=a;}
void changeY(float a){
	y=a;}
void changeZ(float a){
	z=a;}

vector3d operator+(const vector3d& vec2){
	return vector3d(x+vec2.x,y+vec2.y,z+vec2.z);}
vector3d operator-(const vector3d& vec2){
	return vector3d(x-vec2.x,y-vec2.y,z-vec2.z);}

vector3d operator*(float num){
	return vector3d(x*num,y*num,z*num);}

vector3d operator/(float num){
	if(num!=0)	return vector3d(x/num,y/num,z/num);
	else	return vector3d();
}

vector3d& operator+=(const vector3d& vec2){
	x+=vec2.x;	y+=vec2.y;	z+=vec2.z;	return *this;}
vector3d& operator-=(const vector3d& vec2){
	x-=vec2.x;	y-=vec2.y;	z-=vec2.z;	return *this;}
vector3d& operator*=(float num){
	x*=num;	y*=num;	z*=num;	return *this;}
vector3d& operator/=(float num){
	if(num!=0)	{
		x/=num;		y/=num;		z/=num;	}
	return *this;}


bool operator==(const vector3d vec2){
	return (x==vec2.x && y==vec2.y && z==vec2.z);}

bool operator!=(const vector3d vec2){
	!(*this==vec2);}

friend std::ostream& operator<<(std::ostream& out,const vector3d& vec){
	out << vec.x << " " << vec.y << " " << vec.z << std::endl;
	return out;}
};

struct vertexData{
	vector3d position;
	vector3d normal;
	vector3d tangent;
	vector3d color;
	float U,V;
};

struct textureData{
	unsigned int id;
	unsigned int type;
};

class mesh{
	std::vector<vertexData> data;
	std::vector<textureData> textures;
	std::vector<unsigned int> indices;

	public:
	//int mlid;

		mesh(std::vector<vertexData>* vd,std::vector<unsigned int>* id,std::vector<textureData>* td){
	data=*vd;
	indices=*id;
	if(td) textures=*td;
}
		~mesh(){

}



};





class meshLoader{

	std::vector<mesh*> meshes;
	void recursiveProcess(aiNode* node,const aiScene* scene){
	//process

//std::cout<<"NMES"<<node->mNumMeshes<<std::endl;

	for(int i=0;i<node->mNumMeshes;i++)
	{
		aiMesh* meshV=scene->mMeshes[node->mMeshes[i]];
		processMesh(node,scene);
	}
	//recursion
	std::cout<<"NCHI"<<node->mNumChildren<<std::endl;
	for(int i=0;i<node->mNumChildren;i++)
	{
		recursiveProcess(node->mChildren[i],scene);
	}
}
	void processMesh(aiNode* node,const aiScene* scene){


	std::vector<vertexData> data;
	std::vector<unsigned int> indices;
	std::vector<textureData> textures;
	//aiColor4D col;
	//aiMaterial* mat=scene->mMaterials[meshV->mMaterialIndex];
	//aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);
	//vector3d defaultColor(col.r,col.g,col.b);


	glNewList(mlid,GL_COMPILE);
glLineWidth(1);
//glColor3f(0.91,0.41,0.1);

	unsigned int i;
	unsigned int n = 0, t;

glBegin(GL_TRIANGLES);





	// draw all meshes assigned to this node
	for (; n < node->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[node->mMeshes[n]];

		apply_material(scene->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}


		glEnd();

glColor3f(1.0,1.0,1.0);
glEndList();
}

	unsigned int loadTexture(const char* filename)
{
	unsigned int num;
	glGenTextures(1,&num);
	SDL_Surface* img=IMG_Load(filename);
	if(img==NULL)
	{
		//std::cout << "img was not loaded" << std::endl;
		return -1;
	}

	//SDL_PixelFormat form={NULL,32,4,0,0,0,0,0,0,0,0,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2=SDL_ConvertSurface(img,img->format,SDL_SWSURFACE);
	//SDL_Surface *img2 = SDL_ConvertSurfaceFormat(
    //img, SDL_PIXELFORMAT_ARGB8888,SDL_SWSURFACE);

	if(img2==NULL)
	{
		std::cout << "img2 was not loaded" << std::endl;
	return -1;
	}
	glBindTexture(GL_TEXTURE_2D,num);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return num;
}

	public:
		meshLoader(const char* filenameV)
{
	//Assimp::Importer importer;

	const aiScene* sceneV=aiImportFile(filenameV, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);

	if(sceneV->mFlags==AI_SCENE_FLAGS_INCOMPLETE || !sceneV->mRootNode)	{

		std::cout << "The file wasn't successfuly opened " << filenameV << std::endl;
		return;
	}

	recursiveProcess(sceneV->mRootNode,sceneV);

}

		~meshLoader(){
	for(int i=0;i<meshes.size();i++)
		delete meshes[i];
}

		std::vector<mesh*>& getMeshes(){
	return meshes;
}
};



void init()
{
mlid=glGenLists(1);
meshLoader* scene;
	scene=new meshLoader("AX3D/untitled.blend");
}

void display()
{
	glCallList(mlid);

}
*/




/*
void recursive_render (const struct aiScene *sc, const struct aiNode* nd)
{
	unsigned int i;
	unsigned int n = 0, t;
	struct aiMatrix4x4 m = nd->mTransformation;

	// update transform
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);

	// draw all meshes assigned to this node
	for (; n < nd->mNumMeshes; ++n) {
		const struct aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];

		apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		if(mesh->mNormals == NULL) {
			glDisable(GL_LIGHTING);
		} else {
			glEnable(GL_LIGHTING);
		}

		for (t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch(face->mNumIndices) {
				case 1: face_mode = GL_POINTS; break;
				case 2: face_mode = GL_LINES; break;
				case 3: face_mode = GL_TRIANGLES; break;
				default: face_mode = GL_POLYGON; break;
			}

			glBegin(face_mode);

			for(i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if(mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if(mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	// draw all children
	for (n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n]);
	}

	glPopMatrix();
}

*/



// ----------------------------------------------------------------------------




/*void display(void)
{
	float tmp;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

	// rotate it around the y axis
	glRotatef(angle,0.f,1.f,0.f);

	// scale the whole asset to fit into our view frustum
	tmp = scene_max.x-scene_min.x;
	tmp = aisgl_max(scene_max.y - scene_min.y,tmp);
	tmp = aisgl_max(scene_max.z - scene_min.z,tmp);
	tmp = 1.f / tmp;
	glScalef(tmp, tmp, tmp);

        // center the model
	glTranslatef( -scene_center.x, -scene_center.y, -scene_center.z );

        // if the display list has not been made yet, create a new one and
        // fill it with scene contents
	if(scene_list == 0) {
	    scene_list = glGenLists(1);
	    glNewList(scene_list, GL_COMPILE);
            // now begin at the root node of the imported data and traverse
            // the scenegraph by multiplying subsequent local transforms
            // together on GL's matrix stack.

	    glEndList();
	}


}*/










/*class gpath{
int gcid;
float path [];
double xi,yi,zi;

std::stringstream pathss;
std::string gline;


public:
int cline;
int ccline;

gpath(){
xi=0;yi=0;zi=0;
gcid=glGenLists(1);
//glEndList();
}

~gpath(){

}
void u(char* gcode){
//std::ifstream axgtem("AXG.ngc");

pathss<<gcode;

glNewList(gcid,GL_COMPILE);
glLineWidth(1);
glColor3f(0.91,0.41,0.1);
glBegin(GL_LINES);

while( std::getline( pathss, gline ) ) {

 //std::cout<<gline<<'\n';

std::stringstream instruction;
  instruction<<gline;
    glVertex3f(xi,yi,zi);


    while (instruction){


      std::string att;
    instruction>>att;
   // std::cout<<att<<'\n';

     if (att.compare("G0") == 0){
    glColor3f(0.1,0.81,0.1);
    }
if (att.compare("G1") == 0){
glColor3f(0.91,0.41,0.1);

    }

     if (att.compare(0,1,"X") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     xi = strtod (in,0);
    }
        if (att.compare(0,1,"Y") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     yi = strtod (in,0);
    }


        if (att.compare(0,1,"Z") == 0){
     att.erase(0,1);
     char in[15];
     strcpy(in, att.c_str());
     zi = strtod (in,0);
    }


}
glVertex3f(xi,yi,zi);
}
glEnd();
glColor3f(1.0,1.0,1.0);
glEndList();
}

void d(){
glCallList(gcid);

}




};*/

/*class ocam{
public:
float pos[3]={0,0,-300};
float target[3]={0,0,0};
float rx=45,ry=45,rz=0;
ocam(){

}

~ocam(){
}

void u(){
pos[2]-=moscy*(pos[2]/10);

if(rclick){
rx+=(mosx-mosdx);
ry-=(mosdy-mosy);
}
if(mclick){
pos[0]-=(mosx-mosdx)*(pos[2]/800);
pos[1]+=(mosdy-mosy)*(pos[2]/800);
}

if(rx>360)rx=0;if(ry>360)ry=0;if(rz>360)rz=0;
if(rx<0)rx=360;if(ry<0)ry=360;if(rz<0)rz=360;

//if (rx<90){
//ry=ry*((rx-90)/90);
//rz=ry*((rx/90));
//}


}

void d(){
glTranslatef(pos[0],pos[1],pos[2]);

//glRotatef(rx,ry,rx,0);
//glRotatef(rx,0,1,0);

glRotatef(-ry,1,0,0);
glRotatef(rx,0,0,1);
//glRotatef(ry,0,0,1);
//glRotatef(-ry,cos(rx/(180/M_PI)),sin(rx/(180/M_PI)),0);

//glRotatef(rz,0,0,1);
}
};*/

#endif
