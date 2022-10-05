#pragma once
#include "object.h"


class Cube: public Object{
public:
	Cube(std::string fileName):Object(fileName){typeObject=CUBE_OBJ;};
	virtual void step() override;
};
