#include "inputManager.h"

char InputManager::keys[512]={0};


void updateKeys(GLFWwindow* window, int key, int scancode, int action, int mods) {

	switch (action)
	{
	case GLFW_PRESS:
		InputManager::keys[key] = 1;
		break;

	case GLFW_RELEASE:
		InputManager::keys[key] = 0;
		break;


	}

}

void InputManager::init(GLFWwindow* window){

	memset(keys, 0, sizeof(char) * 512);
	glfwSetKeyCallback(window, updateKeys);
	
}


