#pragma once
#include "object.h"




class SpaceShip: public Object{
public:
	SpaceShip(std::string fileName):Object(fileName){typeObject=SPACESHIP_OBJ;};
	virtual void step() override;
};
