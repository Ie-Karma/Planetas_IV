#include "camera.h"
#include "inputManager.h"
#include <iostream>
#include <time.h>



Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, cameraType_e type)
{

    this->position = pos;
    this->lookAt = lookAt;
    this->rotation = glm::vec3(0.0f, 1.0f, 0.0f);
    this->viewMatrix = glm::mat4(1.0f);
    this->type = type;
    this->yaw = 220;
    this->pitch = 0;
	this->roll = 0;
	this->max_roll = 1;

    switch (type) {

    case perspective:
    {
        projMatrix = glm::perspective(glm::radians(initialFoV), 16.0f / 9.0f, 0.00005f, 100.0f);
    }break;

    case ortho:
        projMatrix = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.05f, 100.0f);
        break;
    };


}

void Camera::computeMatrix() {

    this->viewMatrix = glm::lookAt(position, lookAt, rotation);
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

    if (yaw > 360)
    {
        yaw = 0;
    }
    
    if (yaw < 0)
    {
		yaw = 360;
    }

    if (pitch > 360)
    {
        pitch = 0;
    }

    if (pitch < 0)
    {
        pitch = 360;
    }

    if (roll < 0)
    {
		roll = 360;
    }

    if (roll > 360)
    {
		roll = 0;
    }
    
    
    


    glfwGetCursorPos(window,&xpos, &ypos);
    glfwGetWindowSize(window,&screenx, &screeny);
    glfwSetCursorPos(window, 0, 0);

    yaw = yaw + mouseSpeed * xpos;
    pitch = pitch + mouseSpeed * ypos;

    lookAt.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)) + position.x;
    lookAt.y = sin(glm::radians(-pitch)) + position.y;
    lookAt.z = sin(glm::radians(yaw)) * cos(glm::radians(-pitch)) + position.z;

    glm::mat4 right_roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(max_roll), lookAt);
    glm::mat4 left_roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(-max_roll), lookAt);


    //euler rotations matrix
	//glm::mat4 yaw_mat = glm::rotate(glm::mat4(1.0f), glm::radians(yaw), glm::vec3(0.0f, 1.0f, 0.0f));
	//glm::mat4 pitch_mat = glm::rotate(glm::mat4(1.0f), glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f));
    
    
	//lookAt = lookAt * glm::mat3(yaw_mat) * glm::mat3(pitch) * glm::mat3(right_roll_mat);



	std::cout << "yaw: " << yaw << std::endl;
	std::cout << "pitch: " << pitch << std::endl;
	std::cout << "roll: " << roll << std::endl;

    

    
    if (InputManager::keys['Q'])
    {
		rotation = glm::mat3(right_roll_mat) * rotation;
		roll = roll + max_roll;
    }
    
    if (InputManager::keys['E'])
    {
        rotation = glm::mat3(left_roll_mat) * rotation;
		roll = roll - max_roll;
    }

    


	if (InputManager::keys['W'])	{       
     
        position.x += cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * speed;
		position.y += sin(glm::radians(-pitch)) * speed;
		position.z += sin(glm::radians(yaw)) * cos(glm::radians(-pitch)) * speed;        
	}

    if (InputManager::keys['S'])
    {
		position.x -= cos(glm::radians(yaw)) * cos(glm::radians(pitch)) * speed;
		position.y -= sin(glm::radians(-pitch)) * speed;
		position.z -= sin(glm::radians(yaw)) * cos(glm::radians(-pitch)) * speed;
    }

	if (InputManager::keys['A'])
	{
		position.x -= cos(glm::radians(yaw + 90)) * speed;
		position.z -= sin(glm::radians(yaw + 90)) * speed;
	}

    if (InputManager::keys['D'])
    {
		position.x += cos(glm::radians(yaw + 90)) * speed;
		position.z += sin(glm::radians(yaw + 90)) * speed;

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
        position.z += speed * sin(yaw);
        position.x += speed * cos(yaw);
        lookAt.z += speed * sin(yaw);
        lookAt.x += speed * cos(yaw);
    }

    if (InputManager::keys['F'])
    {
        position.x-=speed;
        lookAt.x-=speed;
        position.z -= speed * cos(yaw);
        position.x += speed * sin(yaw);
        lookAt.z -= speed * cos(yaw);
        lookAt.x += speed * sin(yaw);
    }


    if (InputManager::keys['G'])
    {
        position.z+=speed;
        lookAt.z+=speed;
        position.z -= speed * sin(yaw);
        position.x -= speed * cos(yaw);
        lookAt.z -= speed * sin(yaw);
        lookAt.x -= speed * cos(yaw);
    }

    if (InputManager::keys['H'])
    {
        position.x+=speed;
        lookAt.x+=speed;
        position.z += speed * cos(yaw);
        position.x -= speed * sin(yaw);
        lookAt.z += speed * cos(yaw);
        lookAt.x -= speed * sin(yaw);
    }

    if (InputManager::keys['Y']) {
        yaw = (yaw + speed);
        lookAt.x = cos(yaw * PI / 180) + position.x;
        lookAt.z = sin(yaw * PI / 180) + position.z;
    }
 
    
    if (InputManager::keys['R']) {
        yaw = (yaw - speed);
        lookAt.x = cos(yaw * PI / 180) + position.x;
        lookAt.z = sin(yaw * PI / 180) + position.z;
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


