#pragma once
#include "object.h"

class Health: public Object{
public:
    Health(std::string fileName):Object(fileName){typeObject=HEALTH_OBJ;};
    int rest();
};