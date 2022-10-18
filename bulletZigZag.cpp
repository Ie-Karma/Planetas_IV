#include "bulletZigZag.h"
#include "system.h"

void BulletZigZag::step()
{

    if (this->position.y / 0.01f==0)
        std::cout<<"test";
    this->position.y+=direction*0.01f;

    //testColisiones

    std::vector<Object*> *objects=System::scene->getCollisions(SPACESHIP_OBJ, this);

    if(objects->size()>0)
    {
        System::scene->deleteObject(this);
        for(auto it=objects->begin();it!=objects->end();it++)
            System::scene->deleteObject(*it);

    }else	if((this->position.y>2.0f)||(this->position.y< -0.34f))
    {
        System::scene->deleteObject(this);
    }
}

