#include "mesh.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>


Mesh::Mesh() {

	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();

	//añadir vértices

	vertex_t v1, v2, v3;

	v1.posicion = glm::vec4(-0.5f, -0.5, 0.0f, 1.0f);
	v2.posicion = glm::vec4(0.0f, 0.5, 0.0f, 1.0f);
	v3.posicion = glm::vec4(0.5f, -0.5, 0.0f, 1.0f);

	vertexList->push_back(v1);
	vertexList->push_back(v2);
	vertexList->push_back(v3);

	faceList->push_back(0);
	faceList->push_back(1);
	faceList->push_back(2);
}

//CAMBIAR SISTEMA DE PUNTOS

Mesh::Mesh(std::string fileName) {

	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();
	//añadir vértices
	loadFromFile(fileName);
}

std::vector<float> Mesh::computeIcosahedronVertices()
{
	radius = 0.5;
	const float PI = acos(-1);
	const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
	const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree

	std::vector<float> vertices(12 * 3);    // 12 vertices
	int i1, i2;                             // indices
	float z, xy;                            // coords
	float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 2nd row
	float hAngle2 = -PI / 2;                // start from -90 deg at 3rd row

	// the first top vertex (0, 0, r)
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = radius;

	vertex_t topVertex;

	topVertex.posicion.x = 0;
	topVertex.posicion.y = 0;
	topVertex.posicion.z = radius;
	topVertex.posicion.w = 1;

	topVertex.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	topVertex.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	topVertex.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	topVertex.color.w = 1;

	v[0][0] = 0;
	v[0][1] = 0;
	v[0][2] = radius;
	v[0][3] = 0;

	vertexList->push_back(topVertex);



	// 10 vertices at 2nd and 3rd rows
	for (int i = 1; i <= 5; ++i)
	{
		vertex_t v1, v2;

		i1 = i * 3;         // for 2nd row
		i2 = (i + 5) * 3;   // for 3rd row

		z = radius * sinf(V_ANGLE);             // elevaton
		xy = radius * cosf(V_ANGLE);

		vertices[i1] = xy * cosf(hAngle1);      // x
		vertices[i2] = xy * cosf(hAngle2);
		vertices[i1 + 1] = xy * sinf(hAngle1);  // x
		vertices[i2 + 1] = xy * sinf(hAngle2);
		vertices[i1 + 2] = z;                   // z
		vertices[i2 + 2] = -z;

		v[i][0] = xy * cosf(hAngle1);
		v[i][1] = xy * sinf(hAngle1);
		v[i][2] = z;
		v[i][3] = 1;

		v[i + 5][0] = xy * cosf(hAngle2);
		v[i + 5][1] = xy * sinf(hAngle2);
		v[i + 5][2] = -z;
		v[i + 5][3] = 1;

		v1.posicion.x = xy * cosf(hAngle1);      // x
		v1.posicion.y = xy * sinf(hAngle1);  // x
		v1.posicion.z = z;                   // z
		v1.posicion.w = 1;

		v1.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.w = 1;

		v2.posicion.x = xy * cosf(hAngle2);
		v2.posicion.y = xy * sinf(hAngle2);
		v2.posicion.z = -z;
		v2.posicion.w = 1;

		v2.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.w = 1;

		vertexList->push_back(v1);



		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	for (int i = 1; i <= 5; ++i)
	{
		vertex_t v1, v2;

		i1 = i * 3;         // for 2nd row
		i2 = (i + 5) * 3;   // for 3rd row

		z = radius * sinf(V_ANGLE);             // elevaton
		xy = radius * cosf(V_ANGLE);

		vertices[i1] = xy * cosf(hAngle1);      // x
		vertices[i2] = xy * cosf(hAngle2);
		vertices[i1 + 1] = xy * sinf(hAngle1);  // x
		vertices[i2 + 1] = xy * sinf(hAngle2);
		vertices[i1 + 2] = z;                   // z
		vertices[i2 + 2] = -z;

		v[i][0] = xy * cosf(hAngle1);
		v[i][1] = xy * sinf(hAngle1);
		v[i][2] = z;
		v[i][3] = 1;

		v[i + 5][0] = xy * cosf(hAngle2);
		v[i + 5][1] = xy * sinf(hAngle2);
		v[i + 5][2] = -z;
		v[i + 5][3] = 1;

		v1.posicion.x = xy * cosf(hAngle1);      // x
		v1.posicion.y = xy * sinf(hAngle1);  // x
		v1.posicion.z = z;                   // z
		v1.posicion.w = 1;

		v1.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v1.color.w = 1;

		v2.posicion.x = xy * cosf(hAngle2);
		v2.posicion.y = xy * sinf(hAngle2);
		v2.posicion.z = -z;
		v2.posicion.w = 1;

		v2.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		v2.color.w = 1;


		vertexList->push_back(v2);


		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}

	// the last bottom vertex (0, 0, -r)
	i1 = 11 * 3;
	vertices[i1] = 0;
	vertices[i1 + 1] = 0;
	vertices[i1 + 2] = -radius;

	vertex_t botVertex;

	botVertex.posicion.x = 0;
	botVertex.posicion.y = 0;
	botVertex.posicion.z = -radius;
	botVertex.posicion.w = 1;

	botVertex.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	botVertex.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	botVertex.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	botVertex.color.w = 1;

	v[11][0] = 0;
	v[11][1] = 0;
	v[11][2] = -radius;
	v[11][3] = 0;

	vertexList->push_back(botVertex);

	return vertices;
}

Mesh::Mesh(int vertex) {

	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();

	computeIcosahedronVertices();

	const float a = .525731112119233606;
	const float b = .850650808352039932;

	//float v[12][4] = {
	//{-a, 0.0, b, 1.0}, {a, 0.0, b, 1.0}, {-a, 0.0, -b, 1.0}, {a, 0.0, -b, 1.0},
	//{0.0, b, a, 1.0}, {0.0, b, -a, 1.0}, {0.0 ,-b, a, 1.0}, {0.0, -b, -a, 1.0},
	//{b, a, 0.0, 1.0}, {-b, a ,0.0, 1.0}, {b, -a, 0.0, 1.0}, {-b, -a, 0.0, 1.0} };
	int tindices[20][3];
	for (int i = 1; i <= 5; i++)
	{
		tindices[i - 1][0] = 0;
		tindices[i - 1][1] = i;
		tindices[i - 1][2] = 1 + (i % 5);

		tindices[i + 4][0] = i;
		tindices[i + 4][1] = 1 + (i % 5);
		tindices[i + 4][2] = i + 5;

		tindices[i + 9][0] = i + 5;
		tindices[i + 9][1] = 6 + (i % 5);
		tindices[i + 9][2] = 1 + (i % 5);

		tindices[i + 14][0] = 11;
		tindices[i + 14][1] = i + 5;
		tindices[i + 14][2] = 6 + (i % 5);
	}

	//triangle indices
	//int tindices[20][3] = {  //TODO cambiar a formula matematica
	//	{0,1,3}, {0,3,5}, {0,5,7}, {0,7,9}, {0,9,1}, 
	//	{1,2,3}, {3,4,5}, {5,6,7}, {7,8,9}, {9,10,1}, 
	//	{2,3,4}, {4,5,6}, {6,7,8}, {8,9,10}, {10,1,2}, 
	//	{11,2,4}, {11,4,6}, {11,6,8}, {11,8,10}, {11,10,2}
	//};

	int tindices2[20][3] = {
	{0,1,4}, {0,4,9}, {9,4,5}, {4,8,5}, {4,1,8},
	{8,1,10}, {8,10,3}, {5,8,3}, {5,3,2}, {2,3,7},
	{7,3,10}, {7,10,6}, {7,6,11}, {11,6,0}, {0,6,1},
	{6,10,1}, {9,11,0}, {9,2,11}, {9,5,2}, {7,11,2} };

	//for (int i = 0; i < 12; i++)
	//{
	//	vertex_t v1;

	//	v1.posicion.x = v[i][0];
	//	v1.posicion.y = v[i][1];
	//	v1.posicion.z = v[i][2];
	//	v1.posicion.w = v[i][3];

	//	v1.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//	v1.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//	v1.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	//	v1.color.w = 1;



	//	vertexList->push_back(v1);
	//}

	for (int i = 0; i < 20; i++)
	{
		int v1, v2, v3;

		v1 = tindices[i][0];
		v2 = tindices[i][1];
		v3 = tindices[i][2];


		//TODO cambiar a subdivide
		//faceList->push_back(v1);
		//faceList->push_back(v2);
		//faceList->push_back(v3);


		subdivide(v[v1], v[v2], v[v3], v1, v2, v3, 4);

		//std::cout << v[v1] << std::endl;

	}

	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";

	shader = new GLShader(vshader, fshader);

}

void Mesh::normalize(float v[3]) {
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	assert(d > 0);
	v[0] /= d; v[1] /= d; v[2] /= d;

	for (int i = 0; i < 3; i++)
	{
		v[i] *= radius;

		v[i] += (static_cast <float> (rand()) / static_cast <float> (RAND_MAX))/20;
	}
}

void Mesh::subdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth)
{
	float v12[3], v23[3], v31[3];


	int test = vertexList->size();



	if (depth == 0) {
		faceList->push_back(tin1);
		faceList->push_back(tin2);
		faceList->push_back(tin3);
		return;
	}


	for (int i = 0; i < 3; i++)
	{
		v12[i] = (v1[i] + v2[i]) / 2.0;
		v23[i] = (v2[i] + v3[i]) / 2.0;
		v31[i] = (v3[i] + v1[i]) / 2.0;



	}




	normalize(v12);

	vertex_t vertex12;

	vertex12.posicion.x = v12[0];
	vertex12.posicion.y = v12[1];
	vertex12.posicion.z = v12[2];
	vertex12.posicion.w = 1;

	vertex12.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex12.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex12.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex12.color.w = 1;

	vertexList->push_back(vertex12);



	normalize(v23);

	vertex_t vertex23;

	vertex23.posicion.x = v23[0];
	vertex23.posicion.y = v23[1];
	vertex23.posicion.z = v23[2];
	vertex23.posicion.w = 1;

	vertex23.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex23.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex23.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex23.color.w = 1;

	vertexList->push_back(vertex23);

	normalize(v31);

	vertex_t vertex31;

	vertex31.posicion.x = v31[0];
	vertex31.posicion.y = v31[1];
	vertex31.posicion.z = v31[2];
	vertex31.posicion.w = 1;

	vertex31.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex31.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex31.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex31.color.w = 1;

	vertexList->push_back(vertex31);




	subdivide(v1, v12, v31, tin1, test, test + 2, depth - 1);
	subdivide(v2, v23, v12, tin2, test + 1, test, depth - 1);
	subdivide(v3, v31, v23, tin3, test + 2, test + 1, depth - 1);
	subdivide(v12, v23, v31, test, test + 1, test + 2, depth - 1);
}




void Mesh::setColor(int idxVertex, glm::vec4 color) {
	(*vertexList)[idxVertex].color = color;
}


void Mesh::loadFromFile(std::string fileName) {

	std::ifstream fin;
	fin.open(fileName);

	int numVertex = 0;
	fin >> numVertex;
	for (int i = 0; i < numVertex; i++)
	{
		vertex_t v1;
		fin >> v1.posicion.x;
		fin >> v1.posicion.y;
		fin >> v1.posicion.z;
		fin >> v1.posicion.w;

		fin >> v1.color.r;
		fin >> v1.color.g;
		fin >> v1.color.b;
		fin >> v1.color.a;

		fin >> v1.normal.x;
		fin >> v1.normal.y;
		fin >> v1.normal.z;
		fin >> v1.normal.w;
		vertexList->push_back(v1);
	}
	int numFaces = 0;
	fin >> numFaces;
	for (int i = 0; i < numFaces; i++)
	{
		int v1, v2, v3;
		fin >> v1;
		fin >> v2;
		fin >> v3;
		faceList->push_back(v1);
		faceList->push_back(v2);
		faceList->push_back(v3);
	}

	std::string vshader;
	fin >> vshader;
	std::string fshader;
	fin >> fshader;
	fin.close();

	shader = new GLShader(vshader, fshader);
}



Mesh::~Mesh() {

	delete vertexList;
	delete faceList;
}


