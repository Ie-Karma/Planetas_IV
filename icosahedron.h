#pragma once
#include "object.h"


class Icosahedron: public Object
{
public:

	Icosahedron(int vertex) :Object(vertex) { typeObject = CUBE_OBJ; };
	virtual void step() override;
	
};

