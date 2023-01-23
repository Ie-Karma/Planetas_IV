#include "mesh.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <assert.h>
#include <array>



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

Mesh::Mesh(std::string fileName) {

	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();
	loadFromFile(fileName);
}

void Mesh::computeIcosahedronVertices() //Calculo de los vertices del icosaedro de forma matematica desplazando por angulos
{
	radius = 5;
	const float H_ANGLE = PI / 180 * 72;    // 72 degree = 360 / 5
	const float V_ANGLE = atanf(1.0f / 2);  // elevation = 26.565 degree


	int i1, i2;                             // indices
	float z, xy;                            // coords
	float hAngle1 = -PI / 2 - H_ANGLE / 2;  // start from -126 deg at 2nd row
	float hAngle2 = -PI / 2;                // start from -90 deg at 3rd row


	v[0][0] = 0;
	v[0][1] = 0;
	v[0][2] = radius;
	v[0][3] = 0;


	// 10 vertices at 2nd and 3rd rows
	for (int i = 1; i <= 5; ++i)
	{
		vertex_t v1, v2;

		z = radius * sinf(V_ANGLE);             // elevaton
		xy = radius * cosf(V_ANGLE);

		v[i][0] = xy * cosf(hAngle1);
		v[i][1] = xy * sinf(hAngle1);
		v[i][2] = z;
		v[i][3] = 1;

		v[i + 5][0] = xy * cosf(hAngle2);
		v[i + 5][1] = xy * sinf(hAngle2);
		v[i + 5][2] = -z;
		v[i + 5][3] = 1;


		// next horizontal angles
		hAngle1 += H_ANGLE;
		hAngle2 += H_ANGLE;
	}


	v[11][0] = 0;
	v[11][1] = 0;
	v[11][2] = -radius;
	v[11][3] = 0;

	//meter los vertices en vertexList
	for (int i = 0; i < 12; i++)
	{
		vertex_t v1;

		v1.posicion.x = v[i][0];
		v1.posicion.y = v[i][1];
		v1.posicion.z = v[i][2];
		v1.posicion.w = 1;

		

		v1.color.x = 1;
		v1.color.y = 0;
		v1.color.z = 0;
		v1.color.w = 1;

		std::string test1 = std::to_string(v1.posicion.x);
		std::string test2 = std::to_string(v1.posicion.y);
		std::string test3 = std::to_string(v1.posicion.z);

		std::string newKey = test1 + test2 + test3;

		v1.positionInList = vertexList->size();

		sharedVertices.insert({ newKey, v1 });

		vertexList->push_back(v1);
	}


}

Mesh::Mesh(int vertex) {

	vertexList = new std::vector<vertex_t>();
	faceList = new std::vector<int>();

	computeIcosahedronVertices();


	int tindices[20][3];
	for (int i = 1; i <= 5; i++)
	{
		tindices[i - 1][2] = 0;
		tindices[i - 1][1] = i;
		tindices[i - 1][0] = 1 + (i % 5);

		tindices[i + 4][2] = 1 + (i % 5);
		tindices[i + 4][1] = i;		
		tindices[i + 4][0] = i + 5;

		tindices[i + 9][2] = i + 5;
		tindices[i + 9][1] = 6 + (i % 5);
		tindices[i + 9][0] = 1 + (i % 5);

		tindices[i + 14][2] = i + 5;
		tindices[i + 14][1] = 11;	
		tindices[i + 14][0] = 6 + (i % 5);
	}

	for (int i = 0; i < 20; i++)
	{
		int v1, v2, v3;

		v1 = tindices[i][0];
		v2 = tindices[i][1];
		v3 = tindices[i][2];

		std::array<float, 3> vertex0,vertex1,vertex2;
		
		vertex0[0] = v[v1][0];
		vertex0[1] = v[v1][1];
		vertex0[2] = v[v1][2];

		vertex1[0] = v[v2][0];
		vertex1[1] = v[v2][1];
		vertex1[2] = v[v2][2];

		vertex2[0] = v[v3][0];
		vertex2[1] = v[v3][1];
		vertex2[2] = v[v3][2];

		subdividirPorCorte(vertex0, vertex1, vertex2, v1, v2, v3, vertex);
	}

	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";
	std::string tesControlShader = "tesControlShader.txt";
	std::string tesEvaluationShader = "tesEvaluationShader.txt";

	shader = new GLShader(vshader, fshader, tesControlShader, tesEvaluationShader);
	
	tex = new Texture(0, "terrain2");

	std::cout << "Caras: " << faceList->size() / 3 << std::endl;
	std::cout << "Vertices: " << vertexList->size() << std::endl;
}

void Mesh::normalize(std::array<float, 3> &v) {
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	assert(d > 0);
	v[0] /= d; v[1] /= d; v[2] /= d;

	for (int i = 0; i < 3; i++)
	{
		v[i] *= radius;
	}
}


void Mesh::subdividirPorCorte(std::array<float, 3> vertex0, std::array<float, 3> vertex1, std::array<float, 3> vertex2, int triangleIndex0, int triangleIndex1, int triangleIndex2, long depth) {

	std::vector<std::array<float, 3>> triangleSide1,triangleSide2,triangleSide3;

	triangleSide1 = createSides(vertex0, vertex1, depth);

	triangleSide2 = createSides(vertex0, vertex2, depth);

	triangleSide3 = createSides (vertex1, vertex2, depth);

	std::vector<std::vector<std::array<float, 3>>> rowList;

	std::vector<std::array<float, 3>> firstRow;

	firstRow.push_back(triangleSide1[0]);

	rowList.push_back(firstRow);


	for (int i = 1; i < depth + 1; i++)
	{
		std::vector<std::array<float, 3>> row;

		row.push_back(triangleSide1[i]);

		if (i >= 2)
		{
			std::array<float, 3> rowDistance = calculateDistance(triangleSide1[i], triangleSide2[i], i);

			for (int j = 1; j < i; j++)
			{
				row.push_back(moveVertex(triangleSide1[i], multiplyVertex(rowDistance, j)));
			}
		}

		row.push_back(triangleSide2[i]);

		rowList.push_back(row);
	}

	rowList.push_back(triangleSide3);


	for (int i = 1; i < rowList.size(); i++)
	{
		for (int j = 0; j < rowList[i].size() - 1; j++) {

			vertex_t vertice0 = createVertex(rowList[i - 1][j]);

			vertex_t vertice1 = createVertex(rowList[i][j]);

			vertex_t vertice2 = createVertex(rowList[i][j + 1]);


			faceList->push_back(vertice0.positionInList);
			faceList->push_back(vertice1.positionInList);
			faceList->push_back(vertice2.positionInList);

		}

	}

	for (int i = 1; i < rowList.size() - 1; i++)
	{
		for (int j = 0; j < rowList[i].size() - 1; j++) {


			vertex_t inverseVertice0 = createVertex(rowList[i][j]);

			vertex_t inverseVertice1 = createVertex(rowList[i + 1][j + 1]);

			vertex_t inverseVertice2 = createVertex(rowList[i][j + 1]);

			faceList->push_back(inverseVertice0.positionInList);
			faceList->push_back(inverseVertice1.positionInList);
			faceList->push_back(inverseVertice2.positionInList);

		}

	}

}

std::array<float, 3> Mesh::multiplyVertex(std::array<float, 3> vertex, int multiply) {
	std::array<float, 3> newVertex;

	newVertex[0] = vertex[0] * multiply;
	newVertex[1] = vertex[1] * multiply;
	newVertex[2] = vertex[2] * multiply;

	return newVertex;
}

std::array<float, 3> Mesh::moveVertex(std::array<float, 3> vertex, std::array<float, 3> distance) {

	std::array<float, 3> newVertex;

	newVertex[0] = vertex[0] + distance[0];
	newVertex[1] = vertex[1] + distance[1];
	newVertex[2] = vertex[2] + distance[2];

	return newVertex;
}

std::array<float, 3> Mesh::calculateDistance(std::array<float, 3> vertex0, std::array<float, 3> vertex1, long depth) {

	std::array<float, 3> distance;

	distance[0] = vertex1[0] - vertex0[0];
	distance[1] = vertex1[1] - vertex0[1];
	distance[2] = vertex1[2] - vertex0[2];

	distance[0] /= (depth + 1);
	distance[1] /= (depth + 1);
	distance[2] /= (depth + 1);
	return distance;
}

vertex_t Mesh::createVertex(std::array<float, 3> vertex) {

	normalize(vertex);

	vertex_t vertice0;

	vertice0.posicion.x = vertex[0];
	vertice0.posicion.y = vertex[1];
	vertice0.posicion.z = vertex[2];
	vertice0.posicion.w = 1.0f;

	checkSharedVertex(vertice0);

	return vertice0;
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
	std::string texFolder;
	fin >> texFolder;
	fin.close();

	shader = new GLShader(vshader, fshader);
	tex = new Texture(2,texFolder);
}


void Mesh::checkSharedVertex(vertex_t& vertexToCheck) {

	std::string test1 = std::to_string(vertexToCheck.posicion.x);
	std::string test2 = std::to_string(vertexToCheck.posicion.y);
	std::string test3 = std::to_string(vertexToCheck.posicion.z);

	std::string newKey = test1 + test2 + test3;

	if (sharedVertices.find(newKey) != sharedVertices.end()) {

		vertexToCheck.positionInList = sharedVertices[newKey].positionInList;
		
	}
	else
	{

		vertexToCheck.positionInList = vertexList->size();

		sharedVertices.insert({ newKey, vertexToCheck });

		vertexList->push_back(vertexToCheck);

	}

}


std::vector<std::array<float, 3>> Mesh::createSides(std::array<float, 3> vertex0, std::array<float, 3> vertex1, long depth) {

	std::vector<std::array<float, 3>> triangleSide;

	std::array<float, 3> Distance = calculateDistance(vertex0, vertex1, depth);

	triangleSide.push_back(vertex0);


	for (int i = 1; i <= depth; i++)
	{

		triangleSide.push_back(moveVertex(vertex0, multiplyVertex(Distance, i)));

	}

	triangleSide.push_back(vertex1);

	return triangleSide;
}

Mesh::~Mesh() {

	delete vertexList;
	delete faceList;
}