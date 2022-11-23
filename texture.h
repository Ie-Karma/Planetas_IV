#pragma once
#include "common.h"

class Texture{

public:
    int w=0;
    int h=0;
    unsigned int glId=-1;

    unsigned int cubemapTexture;

    Texture(std::string filename);
    Texture();
    void bind(int textureunitIdx);

};