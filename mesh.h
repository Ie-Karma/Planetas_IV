
#pragma once

#include "common.h"
#include "vertex.h"
#include <vector>
#include "shader.h"
#include "texture.h"
#include <array>


class Mesh {

public:
	//atributos
	std::vector<vertex_t>* vertexList;
	std::vector<int>* faceList;
	std::map<std::string, vertex_t> sharedVertices;
	GLShader* shader;
	float v[12][4];
	float radius;
	Texture* tex;

	//métodos	
	Mesh();
	Mesh(std::string fileName);
	Mesh(int vertex);

	void giveColor(vertex_t &vertex);
	
	void recursiveSubdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth);
	void subdividirPorCorte(std::array<float, 3> vertex0, std::array<float, 3> vertex1, std::array<float, 3> vertex2, int triangleIndex0, int triangleIndex1, int triangleIndex2, long depth);
	void subdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth);
	void checkSharedVertex(vertex_t &vertexToCheck);
	void loadFromFile(std::string fileName);
	void setColor(int idxVertex, glm::vec4 color);
	void computeIcosahedronVertices();
	void normalize(std::array<float, 3> &v);
	void normalize(float v[3]);
	void planetShape();
	std::array<float, 3> calculateDistance(std::array<float, 3> vertex0, std::array<float, 3> vertex1, long depth);
	std::array<float, 3> moveVertex(std::array<float, 3> vertex, std::array<float, 3> distance);
	std::array<float, 3> multiplyVertex(std::array<float, 3> vertex, int multiply);


	~Mesh();
};


