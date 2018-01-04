#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>

#include "Transform.h"

#include <string>


#pragma once
class Object
{
public:
	enum Collider { none, aabb, sphere };
	Transform* trnsfrm;
	std::string* textureFileName;
	Collider collider;
	Object();
	Object(Transform* tr, std::string* str, Collider coll);
	~Object();
};

