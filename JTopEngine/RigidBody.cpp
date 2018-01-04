#include "RigidBody.h"



RigidBody::RigidBody()
{
}

RigidBody::RigidBody(glm::vec3 vel, glm::vec3 frc, float mss)
{
	velocity = vel;
	force = frc;
	mass = mss;
}


RigidBody::~RigidBody()
{
}
