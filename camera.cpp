#include "camera.h"
#include "inputManager.h"
#include <iostream>



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

    if (InputManager::keys['T'])
    {
        //        position.z-=0.05f;
        //        lookAt.z-=0.05f;

        position.z += 0.05f * sin(degreesx);
        position.x += 0.05f * cos(degreesx);
        lookAt.z += 0.05f * sin(degreesx);
        lookAt.x += 0.05f * cos(degreesx);

    }

    if (InputManager::keys['F'])
    {
        //        position.x-=0.05f;
        //        lookAt.x-=0.05f;

        position.z -= 0.05f * cos(degreesx);
        position.x += 0.05f * sin(degreesx);
        lookAt.z -= 0.05f * cos(degreesx);
        lookAt.x += 0.05f * sin(degreesx);


    }


    if (InputManager::keys['G'])
    {
        //        position.z+=0.05f;
        //        lookAt.z+=0.05f;

        position.z -= 0.05f * sin(degreesx);
        position.x -= 0.05f * cos(degreesx);
        lookAt.z -= 0.05f * sin(degreesx);
        lookAt.x -= 0.05f * cos(degreesx);
    }

    if (InputManager::keys['H'])
    {
        //        position.x+=0.05f;
        //        lookAt.x+=0.05f;

        position.z += 0.05f * cos(degreesx);
        position.x -= 0.05f * sin(degreesx);
        lookAt.z += 0.05f * cos(degreesx);
        lookAt.x -= 0.05f * sin(degreesx);
    }

    if (InputManager::keys['Y']) {
        degreesx = (degreesx + 0.05f);


        lookAt.x = cos(degreesx) + position.x;
        lookAt.z = sin(degreesx) + position.z;
    }
    if (InputManager::keys['R']) {
        degreesx = (degreesx - 0.05f);


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


