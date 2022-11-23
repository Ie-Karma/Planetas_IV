#include "skybox.h"
#include "inputManager.h"

void Skybox::step() {
	if (InputManager::keys['A'])
	{
		rotation.y -= 0.01f;
	}

	if (InputManager::keys['D'])
	{
		rotation.y += 0.01f;
	}


	if (InputManager::keys['W'])
	{
		rotation.x -= 0.01f;
	}

	if (InputManager::keys['S'])
	{
		rotation.x += 0.01f;
	}
}