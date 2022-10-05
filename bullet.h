#pragma once
#include "object.h"

class Bullet: public Object{

	
public:
	float direction=1.0f;

	Bullet():Object(){};
        Bullet(std::string fileName):Object(fileName){typeObject=BULLET_OBJ;};
	virtual void step() override;
};

