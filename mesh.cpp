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
	//añadir vértices
	loadFromFile(fileName);
}

void Mesh::computeIcosahedronVertices() //Calculo de los vertices del icosaedro de forma matematica desplazando por angulos
{
	radius = 1;
	const float PI = acos(-1);
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

	srand(static_cast <unsigned> (time(0)));

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

		//recursiveSubdivide(v[v1], v[v2], v[v3], v1, v2, v3, vertex);
		subdividirPorCorte(vertex0, vertex1, vertex2, v1, v2, v3, vertex);
	}

	planetShape();

	std::string vshader = "vshader.txt";
	std::string fshader = "fshader.txt";

	shader = new GLShader(vshader, fshader);
	tex = new Texture(3, "terrain");

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

void Mesh::normalize(float v[3]) {
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	assert(d > 0);
	v[0] /= d; v[1] /= d; v[2] /= d;

	for (int i = 0; i < 3; i++)
	{
		v[i] *= radius;
	}
}


void Mesh::subdividirPorCorte(std::array<float, 3> vertex0, std::array<float, 3> vertex1, std::array<float, 3> vertex2, int triangleIndex0, int triangleIndex1, int triangleIndex2, long depth) {
	std::vector<std::array<float, 3>> S1;
	std::vector<std::array<float, 3>> S2;


	std::array<float, 3> s1Distance = calculateDistance(vertex0, vertex1, depth);

	S1.push_back(vertex0);


	for (int i = 1; i <= depth; i++)
	{

		S1.push_back(moveVertex(vertex0, multiplyVertex(s1Distance, i)));


	}

	S1.push_back(vertex1);


	std::array<float, 3> s2Distance = calculateDistance(vertex0, vertex2, depth);




	S2.push_back(vertex0);



	for (int i = 1; i <= depth; i++){

		S2.push_back(moveVertex(vertex0, multiplyVertex(s2Distance, i)));


	}

	S2.push_back(vertex2);

	std::vector<std::vector<std::array<float, 3>>> rowList;

	std::vector<std::array<float, 3>> firstRow;

	firstRow.push_back(S1[0]);

	rowList.push_back(firstRow);


	for (int i = 1; i < depth + 2; i++)
	{
		std::vector<std::array<float, 3>> row;

		row.push_back(S1[i]);


		if (i >= 2)
		{
			std::array<float, 3> rowDistance = calculateDistance(S1[i], S2[i], i);

			for (int j = 1; j < i; j++)
			{

				row.push_back(moveVertex(S1[i], multiplyVertex(rowDistance, j)));
			}
		}

		row.push_back(S2[i]);

		rowList.push_back(row);
	}





		for (int i = 1; i < rowList.size(); i++)
		{
			for (int j = 0; j < rowList[i].size() - 1; j++) {

				normalize(rowList[i - 1][j]);

				vertex_t vertice0;

				vertice0.posicion.x = rowList[i - 1][j][0];
				vertice0.posicion.y = rowList[i - 1][j][1];
				vertice0.posicion.z = rowList[i - 1][j][2];
				vertice0.posicion.w = 1.0f;

				checkSharedVertex(vertice0);

				normalize(rowList[i][j]);

				vertex_t vertice1;

				vertice1.posicion.x = rowList[i][j][0];
				vertice1.posicion.y = rowList[i][j][1];
				vertice1.posicion.z = rowList[i][j][2];
				vertice1.posicion.w = 1.0f;

				checkSharedVertex(vertice1);

				normalize(rowList[i][j + 1]);

				vertex_t vertice2;

				vertice2.posicion.x = rowList[i][j + 1][0];
				vertice2.posicion.y = rowList[i][j + 1][1];
				vertice2.posicion.z = rowList[i][j + 1][2];
				vertice2.posicion.w = 1.0f;

				checkSharedVertex(vertice2);


				faceList->push_back(vertice0.positionInList);
				faceList->push_back(vertice1.positionInList);
				faceList->push_back(vertice2.positionInList);

			}

		}

		for (int i = 1; i < rowList.size()-1; i++)
		{
			for (int j = 0; j < rowList[i].size() - 1; j++) {
				normalize(rowList[i][j]);

				vertex_t inverseVertice0;

				inverseVertice0.posicion.x = rowList[i][j][0];
				inverseVertice0.posicion.y = rowList[i][j][1];
				inverseVertice0.posicion.z = rowList[i][j][2];
				inverseVertice0.posicion.w = 1;

				checkSharedVertex(inverseVertice0);

				normalize(rowList[i + 1][j + 1]);

				vertex_t inverseVertice1;

				inverseVertice1.posicion.x = rowList[i + 1][j + 1][0];
				inverseVertice1.posicion.y = rowList[i + 1][j + 1][1];
				inverseVertice1.posicion.z = rowList[i + 1][j + 1][2];
				inverseVertice1.posicion.w = 1;

				checkSharedVertex(inverseVertice1);

				normalize(rowList[i][j + 1]);

				vertex_t inverseVertice2;

				inverseVertice2.posicion.x = rowList[i][j + 1][0];
				inverseVertice2.posicion.y = rowList[i][j + 1][1];
				inverseVertice2.posicion.z = rowList[i][j + 1][2];
				inverseVertice2.posicion.w = 1;

				checkSharedVertex(inverseVertice2);


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


void Mesh::recursiveSubdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth) {

	float v12[3], v23[3], v31[3];

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


	checkSharedVertex(vertex12);

	normalize(v23);

	vertex_t vertex23;

	vertex23.posicion.x = v23[0];
	vertex23.posicion.y = v23[1];
	vertex23.posicion.z = v23[2];
	vertex23.posicion.w = 1;


	checkSharedVertex(vertex23);

	normalize(v31);

	vertex_t vertex31;

	vertex31.posicion.x = v31[0];
	vertex31.posicion.y = v31[1];
	vertex31.posicion.z = v31[2];
	vertex31.posicion.w = 1;


	checkSharedVertex(vertex31);


	recursiveSubdivide(v1, v12, v31, tin1, vertex12.positionInList, vertex31.positionInList, depth - 1);
	recursiveSubdivide(v2, v23, v12, tin2, vertex23.positionInList, vertex12.positionInList, depth - 1);
	recursiveSubdivide(v3, v31, v23, tin3, vertex31.positionInList, vertex23.positionInList, depth - 1);
	recursiveSubdivide(v12, v23, v31, vertex12.positionInList, vertex23.positionInList, vertex31.positionInList, depth - 1);

}

void Mesh::subdivide(float* v1, float* v2, float* v3, int tin1, int tin2, int tin3, long depth) { //TODO cambiar a cortes por lado

	int newTrianglesPerSide = pow(2, depth);
	int newVerticesPerSide = newTrianglesPerSide - 1;
	int totalNewVertices = newVerticesPerSide * 3;

	float** tempVertex = new float* [totalNewVertices]; //Array de vertices a crear con un tamaño variable dependiendo del numero de subdivision
	for (int i = 0; i < totalNewVertices; i++)
	{
		tempVertex[i] = new float[3];
	}

	float v12TempVertex[3] = { (v2[0] - v1[0]) / newTrianglesPerSide,(v2[1] - v1[1]) / newTrianglesPerSide,(v2[2] - v1[2]) / newTrianglesPerSide }; //dimension del vector de uno de los triangulos
	float v23TempVertex[3] = { (v3[0] - v2[0]) / newTrianglesPerSide,(v3[1] - v2[1]) / newTrianglesPerSide,(v3[2] - v2[2]) / newTrianglesPerSide }; //dimension del vector de uno de los triangulos
	float v31TempVertex[3] = { (v1[0] - v3[0]) / newTrianglesPerSide,(v1[1] - v3[1]) / newTrianglesPerSide,(v1[2] - v3[2]) / newTrianglesPerSide }; //dimension del vector de uno de los triangulos


	for (int i = 0; i < totalNewVertices; i++) //crea los nuevos vertices en orden 
	{
		if (i < newVerticesPerSide)
		{
			for (int j = 0; j < 3; j++)
			{
				tempVertex[i][j] = v1[j] + 1 + i * v12TempVertex[j];
			}
		}
		else if (i >= 2 * newVerticesPerSide)
		{
			for (int j = 0; j < 3; j++)
			{
				tempVertex[i][j] = v1[j] + 1 + i * v23TempVertex[j];
			}

		}
		else
		{
			for (int j = 0; j < 3; j++)
			{
				tempVertex[i][j] = v1[j] + 1 + i * v31TempVertex[j];
			}

		}

	}

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

void Mesh::giveColor(vertex_t& vertex) {
	vertex.color.x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex.color.y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex.color.z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	vertex.color.w = 1;
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

void Mesh::planetShape() {	

	for (int i = 0; i < vertexList->size(); i++)
	{
		float HI = 1.1;
		float LO = 0.95;
		float randomHeight = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

		float randomTest = rand() % 3;

		//if (randomTest==2)
		//{
		//	(*vertexList)[i].posicion.x *= randomHeight;
		//	(*vertexList)[i].posicion.y *= randomHeight;
		//	(*vertexList)[i].posicion.z *= randomHeight;
		//}

		float length = sqrt((*vertexList)[i].posicion.x * (*vertexList)[i].posicion.x
			+ (*vertexList)[i].posicion.y * (*vertexList)[i].posicion.y
			+ (*vertexList)[i].posicion.z * (*vertexList)[i].posicion.z);


		if (length >= radius-0.02 && length <= radius+0.02)
		{
			setColor(i, glm::vec4(0,0.5,0,0));
		}
		else if(length < radius)
		{
			setColor(i, glm::vec4(0, 0, 1, 0));
		}
		else if (length > radius)
		{
			setColor(i, glm::vec4(0.61, 0.61, 0.61, 0));
		}


		
	}
}

Mesh::~Mesh() {

	delete vertexList;
	delete faceList;
}