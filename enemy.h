#pragma once
#include "object.h"

class Enemy: public Object{

	
public:


	Enemy():Object(){};
	Enemy(std::string fileName):Object(fileName){typeObject=ENEMY_OBJ;};
	virtual void step() override;
};

