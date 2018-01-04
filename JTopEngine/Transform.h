#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>

#include "RigidBody.h"

#pragma once
class Transform
{
public:
	glm::vec3 location;
	glm::vec3 rotation;
	glm::vec3 scale;
	glm::mat4 objWorldTrnsfrmMtx; //object world transformation matrix
	RigidBody rgdBdy;
	Transform();
	Transform(glm::vec3 loc, glm::vec3 rot, glm::vec3 scl, RigidBody rgd);
	~Transform();
	void AddGravity();
	void AddNormal();
	void UpdateVelocity();
};

