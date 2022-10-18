#include "object.h"

class MoveBackground: public Object{
public:
    MoveBackground(std::string fileName):Object(fileName){typeObject=MOVEBACKGROUND_OBJ;};
    glm::vec2 scroll = glm::vec2(0.0f,0.0f);
    virtual void step() override;
};

