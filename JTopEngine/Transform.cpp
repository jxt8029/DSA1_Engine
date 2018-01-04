#include "Transform.h"
#include "Engine.h"


Transform::Transform()
{
}

Transform::Transform(glm::vec3 loc, glm::vec3 rot, glm::vec3 scl, RigidBody rgd)
{
	location = loc;
	rotation = rot;
	scale = scl;
	objWorldTrnsfrmMtx = glm::mat4();
	rgdBdy = rgd;
}


Transform::~Transform()
{
}

void Transform::AddGravity()
{
	glm::vec3 cGrav = { 0, 3, 0 };
	rgdBdy.force = rgdBdy.mass * cGrav;
}

void Transform::AddNormal()
{
	rgdBdy.velocity = glm::vec3();
}

void Transform::UpdateVelocity()
{
	/*rgdBdy.velocity.y += (rgdBdy.force.y / rgdBdy.mass) * Engine::GetDeltaTime();
	if (rgdBdy.velocity.y >= 10.f) {
	rgdBdy.velocity.y = 10.f;
	}*/

	// if (rgdBdy.velocity.y > 1.f) 
	// 	rgdBdy.velocity = glm::normalize(rgdBdy.velocity) * 1.f;
	//location += rgdBdy.velocity * Engine::GetDeltaTime();

	rgdBdy.velocity += rgdBdy.force / rgdBdy.mass * Engine::GetDeltaTime();
	rgdBdy.velocity.y = glm::clamp(rgdBdy.velocity.y, -3.f, 3.f);
	location += rgdBdy.velocity * Engine::GetDeltaTime();
	rgdBdy.force = { 0, 0, 0 };
}
