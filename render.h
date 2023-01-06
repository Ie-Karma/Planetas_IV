#pragma once

#include "common.h"
#include "mesh.h"
#include "object.h"
#include "scene.h"

typedef struct bufferObject_t{
	unsigned int abo; //array buffer object ID
	unsigned int vbo; //vertex bufferObject
	unsigned int ibo; //idx bufferObje

}bufferObject_t;

class Render{

private: 
	Camera* cam = nullptr;
	glm::mat4 view=glm::mat4(1.0f);
	glm::mat4 proj=glm::mat4(1.0f);
	std::map<int, bufferObject_t> boList;

public:
	Render();
	void drawMesh(Mesh* mesh,glm::mat4 model);
	void drawObject(Object* obj);
	void drawScene(Scene* scene);
	void setupObject(Object* obj);
	void drawObjectGL4(Object* obj);
	void setCamera(Camera* cam, GLFWwindow* window);
};

