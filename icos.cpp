#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "common.h"

const float a = .525731112119233606;
const float b = .850650808352039932;

//vertices
float v[12][3] = {
	{-a, 0.0, b}, {a, 0.0, b}, {-a, 0.0, -b}, {a, 0.0, -b},
	{0.0, b, a}, {0.0, b, -a}, {0.0 - b, a}, {0.0, -b, -a},
	{b, a, 0.0}, {-b, a ,0.0}, {b, -a, 0.0}, {-b, -a, 0.0} };

//triangle indices
int tindices[20][3] = {
	{0,1,4}, {0,4,9}, {9,4,5}, {4,8,5}, {4,1,8},
	{8,1,10}, {8,10,3}, {5,8,3}, {5,3,2}, {2,3,7},
	{7,3,10}, {7,10,6}, {7,6,11}, {11,6,0}, {0,6,1},
	{6,10,1}, {9,11,0}, {9,2,11}, {9,5,2}, {7,11,2} };

//normalice a vector
void normalize(float v[3]) {
	float d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	assert(d > 0 );
	v[0] /= d; v[1] /= d; v[2] /= d;
}

void init(void) {
	glClearColor(0.5, 0.5, 0.2, 0.5);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	glOrtho(-2.0, 2.0, -2.0, 2.0, 0.1, 100);
}

void getColor(float color[]) {
	static int j = 0;
	j++;
	srand(j);
	for (int i = 0; i < 3; i++) 
		color[i] = (rand() % 256) / 255.0;	
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	//gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	float color[3];
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 20; i++) {
		getColor(color);
		glColor3fv(color); //no tiene efecto con la iluminacion encendida 
		glVertex3fv(&v[tindices[i][0]][0]);
		glVertex3fv(&v[tindices[i][1]][0]);
		glVertex3fv(&v[tindices[i][2]][0]);
	}
	glEnd();
	glFlush();
}

