#pragma once
#include "object.h"


class Icosahedron: public Object
{
public:

	Icosahedron() :Object(1) { typeObject = CUBE_OBJ; };
	virtual void step() override;
	
};

