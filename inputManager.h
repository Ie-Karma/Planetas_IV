#pragma once

#include "common.h"
#include <cstring>
class InputManager{

	public :
		static char keys[512];
		static void init(GLFWwindow* window);
};
