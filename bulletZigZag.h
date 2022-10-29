#pragma once
#include "object.h"

class BulletZigZag: public Object{

public:
    float direction=1.0f;

    BulletZigZag():Object(){};
    BulletZigZag(std::string fileName):Object(fileName){typeObject=BULLET_OBJ;};
    virtual void step() override;

};

