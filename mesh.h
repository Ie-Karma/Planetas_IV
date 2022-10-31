
#pragma once

#include "common.h"
#include "vertex.h"
#include <vector>
#include "shader.h"


class Mesh {

public:
	//atributos
	std::vector<vertex_t>* vertexList;
	std::vector<int>* faceList;
	std::map<std::string, vertex_t> sharedVertices;
	GLShader* shader;
	float v[12][4];
	float radius;

	//métodos	
	Mesh();
	Mesh(std::string fileName);
	Mesh(int vertex);

	void giveColor(vertex_t &vertex);
	
	void recursiveSubdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth);
	void subdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth);
	void checkSharedVertex(vertex_t &vertexToCheck);
	void loadFromFile(std::string fileName);
	void setColor(int idxVertex, glm::vec4 color);
	void computeIcosahedronVertices();
	void normalize(float v[3]);
	void normalize(vertex_t &vertex);

	~Mesh();
};


