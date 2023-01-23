#include "camera.h"
#include "inputManager.h"
#include <iostream>
#include <time.h>



Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type)
{

    this->position = pos;
    this->lookAt = lookAt;
    this->rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->viewMatrix = glm::mat4(1.0f);
    this->type = type;
    this->degreesx = 270;
    this->degreesy = 0;

    switch (type) {

    case perspective:
    {
        projMatrix = glm::perspective(glm::radians(90.0f), 4.0f / 3.0f, 0.05f, 100.0f);
    }break;

    case ortho:
        projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.05f, 100.0f);
        break;
    };


}

void Camera::computeMatrix() {

    this->viewMatrix = glm::lookAt(position, lookAt, glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::vec3 Camera::getPosition() {
    return position;
}

glm::mat4 Camera::getMatrix()
{
    return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() {

    return projMatrix;

}

float clamp(float n, float lower, float upper) {
    return std::max(lower, std::min(n, upper));
}

void Camera::step()
{

    if (degreesx > 360)
    {
        degreesx = 0;
    }
    
    if (degreesx < 0)
    {
		degreesx = 360;
    }

    if (degreesy > 360)
    {
        degreesy = 0;
    }

    if (degreesy < 0)
    {
        degreesy = 360;
    }


    glfwGetCursorPos(window,&xpos, &ypos);
    glfwGetWindowSize(window,&screenx, &screeny);
    glfwSetCursorPos(window, 0, 0);

    degreesx = degreesx + mouseSpeed * xpos;
    degreesy = degreesy + mouseSpeed * ypos;

    lookAt.x = cos(glm::radians(degreesx)) * cos(glm::radians(degreesy)) + position.x;
    lookAt.y = sin(glm::radians(-degreesy)) + position.y;
    lookAt.z = sin(glm::radians(degreesx)) * cos(glm::radians(-degreesy)) + position.z;

	std::cout << "horizontal angle: " << degreesx << std::endl;
	std::cout << "vertical angle: " << degreesy << std::endl;


	if (InputManager::keys['W'])	{       
     
        position.x += cos(glm::radians(degreesx)) * cos(glm::radians(degreesy)) * speed;
		position.y += sin(glm::radians(-degreesy)) * speed;
		position.z += sin(glm::radians(degreesx)) * cos(glm::radians(-degreesy)) * speed;        
	}

    if (InputManager::keys['S'])
    {
		position.x -= cos(glm::radians(degreesx)) * cos(glm::radians(degreesy)) * speed;
		position.y -= sin(glm::radians(-degreesy)) * speed;
		position.z -= sin(glm::radians(degreesx)) * cos(glm::radians(-degreesy)) * speed;
    }

	if (InputManager::keys['A'])
	{
		position.x -= cos(glm::radians(degreesx + 90)) * speed;
		position.z -= sin(glm::radians(degreesx + 90)) * speed;
	}

    if (InputManager::keys['D'])
    {
		position.x += cos(glm::radians(degreesx + 90)) * speed;
		position.z += sin(glm::radians(degreesx + 90)) * speed;

    }

    if (InputManager::keys[' '])
    {


    }

 //   if (InputManager::keys['L'])
 //   {
 //       speed = 0.001f;
 //   }

    if (InputManager::keys['T'])
    {
        position.z-=speed;
        lookAt.z-=speed;
        position.z += speed * sin(degreesx);
        position.x += speed * cos(degreesx);
        lookAt.z += speed * sin(degreesx);
        lookAt.x += speed * cos(degreesx);
    }

    if (InputManager::keys['F'])
    {
        position.x-=speed;
        lookAt.x-=speed;
        position.z -= speed * cos(degreesx);
        position.x += speed * sin(degreesx);
        lookAt.z -= speed * cos(degreesx);
        lookAt.x += speed * sin(degreesx);
    }


    if (InputManager::keys['G'])
    {
        position.z+=speed;
        lookAt.z+=speed;
        position.z -= speed * sin(degreesx);
        position.x -= speed * cos(degreesx);
        lookAt.z -= speed * sin(degreesx);
        lookAt.x -= speed * cos(degreesx);
    }

    if (InputManager::keys['H'])
    {
        position.x+=speed;
        lookAt.x+=speed;
        position.z += speed * cos(degreesx);
        position.x -= speed * sin(degreesx);
        lookAt.z += speed * cos(degreesx);
        lookAt.x -= speed * sin(degreesx);
    }

    if (InputManager::keys['Y']) {
        degreesx = (degreesx + speed);
        lookAt.x = cos(degreesx * PI / 180) + position.x;
        lookAt.z = sin(degreesx * PI / 180) + position.z;
    }
 
    
    if (InputManager::keys['R']) {
        degreesx = (degreesx - speed);
        lookAt.x = cos(degreesx * PI / 180) + position.x;
        lookAt.z = sin(degreesx * PI / 180) + position.z;
    }


    
 //   if (InputManager::keys['P']) {
 //       degreesx = -3.14159265358979323846 / 2;
 //       position = glm::vec3(0, 0, 1.0f);
 //       lookAt = glm::vec3(0, 0, 0);
 //   }

 //   if (InputManager::keys['O']) {
 //       degreesx = -3.14159265358979323846 / 2;
 //       position = glm::vec3(0, 0, 1.0f);
 //       lookAt = glm::vec3(0, 0, 10);
 //   }





}


