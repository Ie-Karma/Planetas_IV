#include "spaceShip.h"
#include "inputManager.h"
#include "scene.h"
#include "system.h"
#include "bullet.h"

void SpaceShip::step()
{


	if(InputManager::keys['A'])
	{
                position.x-=0.01f;
	}	

	if(InputManager::keys['D'])
	{
                position.x+=0.01f;
	}
	
	if(InputManager::keys['T'])
	{ 	
		Object* bullet=new Bullet("bullet.trg");
		bullet->position.x=this->position.x;
		bullet->position.y=this->position.y+0.15f;
		bullet->scale=glm::vec3(0.1f,0.1f,0.1);
		System::scene->addObject(bullet);
	}

	
}

