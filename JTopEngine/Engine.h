#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>

#include <string>
#include <time.h>
#include "Object.h"


#pragma once
class Engine
{
public:
	static float t, t0, dt; //time variables
	enum Collider{none, aabb, sphere};
	GLFWwindow* GLFWwindowPtr;
	Engine();
	~Engine();
	int load();
	static float GetDeltaTime();
	static void UpdateTime();
	static bool CollidesWith(Object* obj1, Object* obj2);
};


