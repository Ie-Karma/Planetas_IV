#pragma once

#include "common.h"
#include "mesh.h"
#include "collider.h"
#include "shader.h"

class Object{

	static int idCounter;
public:
	int id=0;
	int typeObject;
	bool markedDelete=false;
	glm::mat4 modelMatrix;
	glm::vec3 position=glm::vec3(0,0,0);
	glm::vec3 rotation=glm::vec3(0,0,0);
	glm::vec3 scale=glm::vec3(1.0f,1.0f,1.0f);

	Mesh* mesh;
	GLShader* shader;
	
	Collider* collider;
		
	Object();
	Object(int vertex);
	Object(std::string fileName);
	glm::mat4 getMatrix();
	void computeMatrix();
	void updateCollider();
	virtual void step();
	
	
};
