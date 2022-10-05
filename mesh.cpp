#include "mesh.h"
#include <iostream>
#include <fstream>


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
