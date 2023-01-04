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
    this->degreesx = -3.14159265358979323846 / 2;
    this->degreesy = -3.14159265358979323846 / 2;

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

void Camera::step()
{




 //   glfwGetCursorPos(window,&xpos, &ypos);
 //   glfwGetWindowSize(window,&screenx, &screeny);
 //   glfwSetCursorPos(window, 0, 0);

 //   horizontalAngle = mouseSpeed * xpos;
 //   verticalAngle = mouseSpeed * ypos;

 //   degreesx = (degreesx + horizontalAngle);
 //   degreesy = (degreesy + verticalAngle);

 //   float lookAtz1, lookAtz2;

 //   lookAtz1 = sin(degreesx) + position.z;
 //   lookAtz2 = cos(degreesy) + position.z;

 //   lookAt.x = cos(degreesx) + position.x;
 //   
 //   lookAt.z = lookAtz1 + lookAtz2;
 //   
 //   lookAt.y = sin(degreesy) + position.y;

	//std::cout << "vertical angle: " << degreesx << std::endl;
	//std::cout << "horizontal angle: " << degreesy << std::endl;



    if (InputManager::keys['L'])
    {
        speed = 0.001f;
    }

    if (InputManager::keys['T'])
    {
        //        position.z-=speed;
        //        lookAt.z-=speed;

        position.z += speed * sin(degreesx);
        position.x += speed * cos(degreesx);
        lookAt.z += speed * sin(degreesx);
        lookAt.x += speed * cos(degreesx);

    }

    if (InputManager::keys['F'])
    {
        //        position.x-=speed;
        //        lookAt.x-=speed;

        position.z -= speed * cos(degreesx);
        position.x += speed * sin(degreesx);
        lookAt.z -= speed * cos(degreesx);
        lookAt.x += speed * sin(degreesx);


    }


    if (InputManager::keys['G'])
    {
        //        position.z+=speed;
        //        lookAt.z+=speed;

        position.z -= speed * sin(degreesx);
        position.x -= speed * cos(degreesx);
        lookAt.z -= speed * sin(degreesx);
        lookAt.x -= speed * cos(degreesx);
    }

    if (InputManager::keys['H'])
    {
        //        position.x+=speed;
        //        lookAt.x+=speed;

        position.z += speed * cos(degreesx);
        position.x -= speed * sin(degreesx);
        lookAt.z += speed * cos(degreesx);
        lookAt.x -= speed * sin(degreesx);
    }

    if (InputManager::keys['Y']) {
        degreesx = (degreesx + speed);


        lookAt.x = cos(degreesx) + position.x;
        lookAt.z = sin(degreesx) + position.z;
    }
    if (InputManager::keys['R']) {
        degreesx = (degreesx - speed);


        lookAt.x = cos(degreesx) + position.x;
        lookAt.z = sin(degreesx) + position.z;
    }
    if (InputManager::keys['P']) {
        degreesx = -3.14159265358979323846 / 2;
        position = glm::vec3(0, 0, 1.0f);
        lookAt = glm::vec3(0, 0, 0);
    }

    if (InputManager::keys['O']) {
        degreesx = -3.14159265358979323846 / 2;
        position = glm::vec3(0, 0, 1.0f);
        lookAt = glm::vec3(0, 0, 10);
    }





}


