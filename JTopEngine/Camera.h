#include <FreeImage.h>

#include <GL\glew.h>   
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp> //to use glm::perspective
#include <glm\gtx\euler_angles.hpp> //to use glm::yawPitchRoll

#include "Engine.h"

#pragma once
class Camera
{
public:
	glm::mat4 worldView; //default is identity matrix
	GLFWwindow* window = glfwGetCurrentContext();
	Object object;
	Transform trnsfrm;
	Object::Collider collider = Object::sphere;
	int width, height;
	float zoom;
	float fovy;
	float aspect;
	float zNear;
	float zFar;
	glm::vec3 camLoc = { 0, 0, 0 };
	glm::vec3 velocity = glm::vec3();
	glm::mat3 rotMat; //rotation matrix
	glm::vec3 camRot = { 0, 0, 0 }; //rotation angle
	Camera();
	~Camera();
	void upload();
	void start(); //may not need
	void turn();
	void move();
};

