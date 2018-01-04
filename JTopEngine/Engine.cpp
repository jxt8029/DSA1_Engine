#include "Engine.h"


float Engine::t = 0;
float Engine::t0 = 0;
float Engine::dt = 0;

void Engine::UpdateTime()
{
	t0 = t;
	t = (float)glfwGetTime();
	dt = t - t0;
}

bool Engine::CollidesWith(Object * obj1p, Object * obj2p)
{
	Object* obj1 = obj1p;
	Object* obj2 = obj2p;

	//no colliders
	if (obj1->collider == Engine::none && obj2->collider == Engine::none)
	{
		return false;
	}

	//sphere colliders
	if (obj1->collider == Engine::sphere && obj2->collider == Engine::sphere)
	{
		float distance = pow((obj1->trnsfrm->location.z - obj2->trnsfrm->location.z), 2) + pow((obj1->trnsfrm->location.x - obj2->trnsfrm->location.x), 2) + pow((obj1->trnsfrm->location.y - obj2->trnsfrm->location.y), 2);
		distance = sqrt(distance);
		if (distance < obj1->trnsfrm->scale.x + obj2->trnsfrm->scale.x)
		{
			return true;
		}
		return false;
	}

	//aabb colliders
	if (obj1->collider == Engine::aabb && obj2->collider == Engine::aabb)
	{
		bool x, y, z = false;

		//x axis
		if (obj2->trnsfrm->location.x - obj2->trnsfrm->scale.x < obj1->trnsfrm->location.x + obj1->trnsfrm->scale.x || obj2->trnsfrm->location.x + obj2->trnsfrm->scale.x > obj1->trnsfrm->location.x - obj1->trnsfrm->scale.x)
		{
			x = true;
		}
		//y axis
		if (obj2->trnsfrm->location.y - obj2->trnsfrm->scale.y < obj1->trnsfrm->location.y + obj1->trnsfrm->scale.y || obj2->trnsfrm->location.y + obj2->trnsfrm->scale.y > obj1->trnsfrm->location.y - obj1->trnsfrm->scale.y)
		{
			y = true;
		}
		//z axis
		if (obj2->trnsfrm->location.z - obj2->trnsfrm->scale.z < obj1->trnsfrm->location.z + obj1->trnsfrm->scale.z || obj2->trnsfrm->location.z + obj2->trnsfrm->scale.z > obj1->trnsfrm->location.z - obj1->trnsfrm->scale.z)
		{
			z = true;
		}

		if (x == true && y == true && z == true)
		{
			return true;
		}
		return false;
	}

	//sphere and aabb colliders
	if ((obj1->collider == Engine::sphere && obj2->collider == Engine::aabb))
	{
		float distance = 0.0f;

		//x axis
		if (obj1->trnsfrm->location.x > obj2->trnsfrm->location.x - obj2->trnsfrm->scale.x && obj1->trnsfrm->location.x < obj2->trnsfrm->location.x + obj2->trnsfrm->scale.x)
		{
			distance += 0.0f;
		}
		else if (obj1->trnsfrm->location.x > obj2->trnsfrm->location.x + obj2->trnsfrm->scale.x)
		{
			distance += pow((obj1->trnsfrm->location.x - (obj2->trnsfrm->location.x + obj2->trnsfrm->scale.x)), 2);
		}
		else if (obj1->trnsfrm->location.x < obj2->trnsfrm->location.x - obj2->trnsfrm->scale.x)
		{
			distance += pow(((obj2->trnsfrm->location.x + obj2->trnsfrm->scale.x) - obj1->trnsfrm->location.x), 2);
		}

		//y axis
		if (obj1->trnsfrm->location.y > obj2->trnsfrm->location.y - obj2->trnsfrm->scale.y && obj1->trnsfrm->location.y < obj2->trnsfrm->location.y + obj2->trnsfrm->scale.y)
		{
			distance += 0.0f;
		}
		else if (obj1->trnsfrm->location.y > obj2->trnsfrm->location.y + obj2->trnsfrm->scale.y)
		{
			distance += pow((obj1->trnsfrm->location.y - (obj2->trnsfrm->location.y + obj2->trnsfrm->scale.y)), 2);
		}
		else if (obj1->trnsfrm->location.y < obj2->trnsfrm->location.y - obj2->trnsfrm->scale.y)
		{
			distance += pow(((obj2->trnsfrm->location.y + obj2->trnsfrm->scale.y) - obj1->trnsfrm->location.y), 2);
		}

		//z axis
		if (obj1->trnsfrm->location.z > obj2->trnsfrm->location.z - obj2->trnsfrm->scale.z && obj1->trnsfrm->location.z < obj2->trnsfrm->location.z + obj2->trnsfrm->scale.z)
		{
			distance += 0.0f;
		}
		else if (obj1->trnsfrm->location.z > obj2->trnsfrm->location.z + obj2->trnsfrm->scale.z)
		{
			distance += pow((obj1->trnsfrm->location.z - (obj2->trnsfrm->location.z + obj2->trnsfrm->scale.z)), 2);
		}
		else if (obj1->trnsfrm->location.z < obj2->trnsfrm->location.z - obj2->trnsfrm->scale.z)
		{
			distance += pow(((obj2->trnsfrm->location.z + obj2->trnsfrm->scale.z) - obj1->trnsfrm->location.z), 2);
		}

		distance = sqrt(distance);

		if (distance < obj1->trnsfrm->scale.x)
		{
			return true;
		}
		return false;
	}
	return true;
}

Engine::Engine()
{
}


Engine::~Engine()
{
}

int Engine::load()
{
	if (glfwInit() == GL_FALSE)
		return -1;

	GLFWwindowPtr = glfwCreateWindow(800, 600, "Jake Toporoff DSA1 Engine", NULL, NULL);

	if (GLFWwindowPtr != nullptr)
		glfwMakeContextCurrent(GLFWwindowPtr);
	else {
		glfwTerminate();
		return -1;
	}

	if (glewInit() != GLEW_OK) {
		glfwTerminate();
		return -1;
	}

	glClearColor(.4f, .65f, .1f, 1.0f); //Set color (please, anything but cornflower blue)

	glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	//Wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Backface culling
	glEnable(GL_DEPTH_TEST);

	return 0;
}

float Engine::GetDeltaTime()
{
	return dt;
}
