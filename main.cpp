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
#include "icosahedron.h"




bool renderfps(double framerate, GLFWwindow* window)
{
	static double lastTime = 0;
	static double currentTime = 0;
	double timeDiff;
	int counter = 0;
	
	

	currentTime = glfwGetTime();
	timeDiff = currentTime - lastTime;
	counter++;
	if (timeDiff >= 1.0 / framerate)
	{
		std::string FPS = std::to_string((1.0 / timeDiff) * counter);
		std::string ms = std::to_string((timeDiff / counter) * 1000);
		std::string newTitle = "Planetas IV - " + FPS + "FPS / " + ms + "ms";
		glfwSetWindowTitle(window, newTitle.c_str());
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


	GLFWwindow* window = glfwCreateWindow(1920, 1080, "Prueba 1 GLFW", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	

	int glewState = glewInit();

	if (glewState != GLEW_OK)
		std::cout << "ERROR iniciando glew\n";

	InputManager::init(window);


	Render* render = new Render();
	Scene* scene = new Scene();
	System::scene = scene;
	scene->setCamera(new Camera(glm::vec3(0, 0, 0.25), glm::vec3(0, 0, 0), perspective),window);
	render->setCamera(scene->getCamera(), window);



	Object* icosahedron = new Icosahedron(10);
	icosahedron->position.z -= 2;
	render->setupObject(icosahedron);
	scene->addObject(icosahedron);

	Object* cube = new Cube("cube.trg");
	render->setupObject(cube);
	scene->addObject(cube);
	cube->scale *= 50;

	while (!glfwWindowShouldClose(window))
	{

		if (renderfps(60.0f, window)) {
			scene->step(0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			render->drawScene(scene);
			glfwSwapBuffers(window);
			glfwPollEvents();

			//close window
			if (InputManager::keys['C'])
			{
				glfwSetWindowShouldClose(window, true);
			}
		}

	}

	//delete icosahedron;

	return 0;

}

