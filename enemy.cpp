#include "enemy.h"
#include "system.h"
#include "bullet.h"


void Enemy::step()
{
        this->position.x+=0.01f;
	
	int random=((int)rand())%100;
	if(random==0)
	{
		Bullet* bullet=new Bullet("bullet.trg");
		bullet->direction=-1.0f;
		bullet->position.x=this->position.x;
        bullet->position.y=this->position.y-0.25f;
		bullet->scale=glm::vec3(0.1f,0.1f,0.1f);
		System::scene->addObject(bullet);
	}
	if(this->position.x>1.0f)
	{
		this->position.x=-1.0f;
	}

}
