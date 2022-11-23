#pragma once
#include "common.h"

typedef enum cameraType_e {
	perspective, ortho
}cameraType_e;

class Camera {
public:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 lookAt;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	double degreesx;
	double degreesy;
	cameraType_e type;


	Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type);
	void step();
	void computeMatrix();
	glm::vec3 getPosition();
	glm::mat4 getMatrix();
	glm::mat4 getProjectionMatrix();

};
