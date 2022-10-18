#pragma once

#include "common.h"
#include "vertex.h"
#include <vector>
#include "shader.h"

class Mesh{

public:
//atributos
	std::vector<vertex_t>* vertexList;
	std::vector<int>* faceList;
	GLShader* shader;
//métodos	
	Mesh();
	Mesh(std::string fileName);
	Mesh(int vertex);
	~Mesh();
	void subdivide(float *v1, float *v2, float *v3, long depth);
	void loadFromFile(std::string fileName);
	void setColor(int idxVertex, glm::vec4 color);
};
