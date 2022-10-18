#include "object.h"

class Background: public Object{
public:
    Background(std::string fileName):Object(fileName){typeObject=BACKGROUND_OBJ;};
    glm::vec2 scroll = glm::vec2(0.0f,0.0f);
    virtual void step() override;
};

