#include "mesh.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>


Mesh::Mesh(){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();

//añadir vértices

	vertex_t v1,v2,v3;
	
	v1.posicion=glm::vec4(-0.5f,-0.5,0.0f,1.0f);
	v2.posicion=glm::vec4( 0.0f, 0.5,0.0f,1.0f);
	v3.posicion=glm::vec4( 0.5f,-0.5,0.0f,1.0f);
	
	vertexList->push_back(v1);
	vertexList->push_back(v2);
	vertexList->push_back(v3);
	
	faceList->push_back(0);
	faceList->push_back(1);
	faceList->push_back(2);
}



Mesh::Mesh(std::string fileName){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();
//añadir vértices
	loadFromFile(fileName);
}

Mesh::Mesh(int vertex) {
	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();

	const float a = .525731112119233606;
	const float b = .850650808352039932;

	float v[12][4] = {
	{-a, 0.0, b, 1.0}, {a, 0.0, b, 1.0}, {-a, 0.0, -b, 1.0}, {a, 0.0, -b, 1.0},
	{0.0, b, a, 1.0}, {0.0, b, -a, 1.0}, {0.0 ,-b, a, 1.0}, {0.0, -b, -a, 1.0},
	{b, a, 0.0, 1.0}, {-b, a ,0.0, 1.0}, {b, -a, 0.0, 1.0}, {-b, -a, 0.0, 1.0} };
	
	//triangle indices
	int tindices[20][3] = {
		{0,1,4}, {0,4,9}, {9,4,5}, {4,8,5}, {4,1,8},
		{8,1,10}, {8,10,3}, {5,8,3}, {5,3,2}, {2,3,7},
		{7,3,10}, {7,10,6}, {7,6,11}, {11,6,0}, {0,6,1},
		{6,10,1}, {9,11,0}, {9,2,11}, {9,5,2}, {7,11,2} };

	for (int i = 0; i < 12; i++)
	{
		vertex_t v1;

		v1.posicion.x = v[i][0];
		v1.posicion.y = v[i][1];
		v1.posicion.z = v[i][2];
		v1.posicion.w = v[i][3];

		v1.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.w = 1;



		vertexList->push_back(v1);
	}

	for (int i = 0; i < 20; i++)
	{
		int v1, v2, v3;

		v1 = tindices[i][0];
		v2 = tindices[i][1];
		v3 = tindices[i][2];




		faceList->push_back(v1);
		faceList->push_back(v2);
		faceList->push_back(v3);

		
	}

	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";

	shader = new GLShader(vshader, fshader);

}

void normalize(float v[3]) {
	float d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
	assert(d > 0);
	v[0] /= d; v[1] /= d; v[2] /= d;
}

void Mesh::subdivide(float* v1, float* v2, float* v3, long depth)
{
	float v12[3], v23[3], v31[3];
	int i;

	if (depth == 0) {
		faceList->push_back((int) v1[0]);
		faceList->push_back((int) v2[0]);
		faceList->push_back((int) v3[0]);
		return;
	}


	for ( i = 0; i < 3; i++)
	{
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;
	}

	normalize(v12);
	normalize(v23);
	normalize(v31);
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}




void Mesh::setColor(int idxVertex, glm::vec4 color){
	(*vertexList)[idxVertex].color=color;
}


void Mesh::loadFromFile(std::string fileName){

	std::ifstream fin;
	fin.open(fileName);
	
	int numVertex=0;
	fin>>numVertex;
	for(int i=0;i<numVertex;i++)
	{
		vertex_t v1;
		fin>>v1.posicion.x;
		fin>>v1.posicion.y;
		fin>>v1.posicion.z;
		fin>>v1.posicion.w;

		fin>>v1.color.r;
		fin>>v1.color.g;
		fin>>v1.color.b;
		fin>>v1.color.a;
		
		fin>>v1.normal.x;
		fin>>v1.normal.y;
		fin>>v1.normal.z;
		fin>>v1.normal.w;
		vertexList->push_back(v1);	
	}
	int numFaces=0;
	fin>>numFaces;
	for(int i=0;i<numFaces;i++)
	{
		int v1,v2,v3;
		fin>>v1;
		fin>>v2;
		fin>>v3;
		faceList->push_back(v1);			
		faceList->push_back(v2);
		faceList->push_back(v3);	
	}
	
	std::string vshader;
	fin>>vshader;
	std::string fshader;
	fin>>fshader;
	fin.close();
	
	shader=new GLShader(vshader,fshader);
}



Mesh::~Mesh(){
	
	delete vertexList;
	delete faceList;
}


	