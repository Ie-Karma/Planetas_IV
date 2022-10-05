#include "cube.h"
#include "inputManager.h"
#include "scene.h"
#include "system.h"


void Cube::step()
{


	if(InputManager::keys['A'])
	{
                rotation.y-=0.01f;
	}	

	if(InputManager::keys['D'])
	{
                rotation.y+=0.01f;
	}
	
	
	if(InputManager::keys['W'])
	{
                rotation.x-=0.01f;
	}	

	if(InputManager::keys['S'])
	{
                rotation.x+=0.01f;
	}

}

