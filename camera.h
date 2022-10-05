#pragma once
#include "common.h"

typedef enum cameraType_e{
	perspective, ortho
}cameraType_e;

class Camera{
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 lookAt;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	cameraType_e type;
public:
	Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type);
	void step();
	void computeMatrix();
	glm::mat4 getMatrix();
	glm::mat4 getProjectionMatrix();

};
