#pragma once
#include "object.h"

class Skybox: public Object
{
public:
	Skybox(int test,int test2) :Object(test, test2) { typeObject = PLANET_OBJ; };
	virtual void step() override;
};

