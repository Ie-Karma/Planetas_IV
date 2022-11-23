#pragma once

#include "common.h"


typedef struct vertex_t{

	glm::vec4 posicion;
	glm::vec4 color;
	glm::vec4 normal;
	int positionInList;
	glm::vec2 texCoord;
}vertex_t;


