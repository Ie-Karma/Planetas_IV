#pragma once
#include "common.h"

class Texture{

public:
    int w=0;
    int h=0;
    int textType;
    unsigned int glId=-1;

    Texture(std::string filename);
    Texture(int textType);
    void bind(int textureunitIdx);

};