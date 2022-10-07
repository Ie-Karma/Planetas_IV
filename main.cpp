#include <iostream>
#include "common.h"
#include <vector>
#include "mesh.h"
#include "render.h"
#include "object.h"
#include "scene.h"
#include "inputManager.h"
#include "spaceShip.h"
#include "system.h"

#include "enemy.h"
#include "cube.h"
#include <GL/glut.h>

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
	assert(d > 0);
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
	gluLookAt(8.0, 8.0, 8.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
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



bool renderfps(double framerate)
{
	static double currentTime = 0;
	static double lastTime = 0;

	currentTime = glfwGetTime();
	if (currentTime - lastTime >= 1.0 / framerate)
	{
		lastTime = currentTime;
		return true;
	}
	return false;
}


int main(int argc, char** argv)
{

	int glfwState = glfwInit();
	if (!glfwState)
		std::cout << "ERROR iniciando glfw\n";

	GLFWwindow* window = glfwCreateWindow(640, 480, "Prueba 1 GLFW", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	int glewState = glewInit();

	if (glewState != GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);
	/*	Object* triangle=new SpaceShip("triangle.trg");
		triangle->scale=glm::vec3(0.1f,0.1f,0.1f);
		triangle->position.y=-0.45f;


		Object* enemy=new Enemy("triangle.trg");
		enemy->scale=glm::vec3(0.1f,0.1f,0.1f);
		enemy->position.y=0.45f;
		enemy->rotation.z=glm::radians(180.0f);
		*/
	Render* render = new Render();
	Scene* scene = new Scene();
	System::scene = scene;
	scene->setCamera(new Camera(glm::vec3(0, 0, 0.25), glm::vec3(0, 0, 0), perspective));
	//scene->addObject(triangle);
	//scene->addObject(enemy);

	//render->setupObject(enemy);
	//render->setupObject(triangle);

	//Object* cube = new Cube("cube.trg");
	//cube->scale=glm::vec3(0.5f,0.5f,0.5f);
	//cube->position.z = -3.0f;

	//render->setupObject(cube);
	//scene->addObject(cube);

	while (!glfwWindowShouldClose(window))
	{

		if (renderfps(60.0f)) {
			display();
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	//delete triangle;
	return 0;

}

