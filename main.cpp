#include <iostream>
#include "common.h"
#include <vector>
#include "mesh.h"
#include "render.h"
#include "object.h"
#include "scene.h"
#include "inputManager.h"
#include "system.h"

#include "cube.h"
#include "icosahedron.h"




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


	GLFWwindow* window = glfwCreateWindow(1080, 810, "Prueba 1 GLFW", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);


	int glewState = glewInit();

	if (glewState != GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);



	Render* render = new Render();
	Scene* scene = new Scene();
	System::scene = scene;
	scene->setCamera(new Camera(glm::vec3(0, 0, 0.25), glm::vec3(0, 0, 0), perspective));

	Object* cube = new Cube("cube.trg");
	render->setupObject(cube);
	scene->addObject(cube);


	//Object* icosahedron = new Icosahedron(4);
	//icosahedron->position.z -= 2;
	//render->setupObject(icosahedron);
	//scene->addObject(icosahedron);

	while (!glfwWindowShouldClose(window))
	{

		if (renderfps(60.0f)) {
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	//delete icosahedron;

	return 0;

}

