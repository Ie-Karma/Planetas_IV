#pragma once

#include "common.h"
#include "object.h"


class SpatialHashing{

public:

	std::map<int,Object*> *objList=nullptr;
	int numFilas;
	int numColumnas;
	float tamX, tamY;
	float minX, minY;
	std::map<int,Object*>** grid;
	
	SpatialHashing(std::map<int,Object*> *objList,	int numFilas,int numColumnas, float minX, float minY, float tamX, float tamY );
	
	void update();

};
