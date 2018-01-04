#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>

#pragma once
class RigidBody
{
public:
	glm::vec3 velocity;
	glm::vec3 force;
	float mass;
	RigidBody();
	RigidBody(glm::vec3 vel, glm::vec3 frc, float mss);
	~RigidBody();
};

