#pragma once
#include "common.h"


typedef enum cameraType_e {
	perspective, ortho
}cameraType_e;

class Camera {
private:
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 lookAt;
	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	float yaw;
	float pitch;
	float roll;
	float max_roll;
	cameraType_e type;

	float horizontalAngle = 0;
	// vertical angle : 0, look at the horizon
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 90.0f;

	float mouseSpeed = 0.1f;

	double xpos, ypos;
	int screenx, screeny;
	float speed = 0.05f;


public:

	Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type);
	void step();
	void computeMatrix();
	glm::vec3 getPosition();
	glm::mat4 getMatrix();
	glm::mat4 getProjectionMatrix();

	GLFWwindow* window;

};
