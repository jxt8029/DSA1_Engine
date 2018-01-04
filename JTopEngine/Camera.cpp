#include "Camera.h"

#include "RigidBody.h"
#include "Transform.h"
#include "Object.h"

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::upload()
{
	rotMat = (glm::mat3)glm::yawPitchRoll(trnsfrm.rotation.y, trnsfrm.rotation.x, trnsfrm.rotation.z);

	zoom = 1.f;
	aspect = (float)width / (float)height;
	fovy = 3.14159f * .4f / zoom;
	zNear = .01f;
	zFar = 1000.f;

	//calculate lookAt matrix
	glm::vec3 eye = trnsfrm.location;
	if (eye.z != 2.0f) {
		char a = 0;
	}
	glm::vec3 center = eye + rotMat * glm::vec3(0, 0, -1);
	glm::vec3 up = rotMat * glm::vec3(0, 1, 0);
	glm::mat4 lookAtMat = glm::lookAt(eye, center, up);
	
	//calculate perspective matrix
	glm::mat4 perspectiveMat = glm::perspective(fovy, aspect, zNear, zFar);

	//calculate worldView matrix and pass to vShader
	worldView = perspectiveMat * lookAtMat;
	glUniformMatrix4fv(1, 1, GL_FALSE, &worldView[0][0]);

	//pass camLoc to fShader
	glUniform3f(5, trnsfrm.location.x, trnsfrm.location.y, trnsfrm.location.z);

	//set lightLoc and pass data to fShader
	glm::vec3 lightLoc = glm::vec3(5.f, 5.f, 5.f);
	glUniform3f(6, lightLoc.x, lightLoc.y, lightLoc.z);
}

void Camera::start()
{
	worldView = glm::mat4(); //identity matrix

	//get window size and set default mouse position
	glfwGetWindowSize(window, &width, &height);
	glfwSetCursorPos(window, width / 2, height / 2);

	std::string plchldr = "";
	trnsfrm = Transform(camLoc, camRot, glm::vec3(1, 1, 1), RigidBody(velocity, glm::vec3(0, 0, 0), 1));
	object = Object(&trnsfrm, &plchldr, collider);
}

void Camera::turn()
{
	float sensitivity = .005f;
	float pi = 3.14159f;
	double cursorX, cursorY;
	glfwGetCursorPos(window, &cursorX, &cursorY);

	trnsfrm.rotation.y -= sensitivity * (float)(cursorX - width / 2);
	trnsfrm.rotation.x -= sensitivity * (float)(cursorY - height / 2);
	trnsfrm.rotation.x = glm::clamp(trnsfrm.rotation.x, (-1 * pi) / 2, pi / 2);
	glfwSetCursorPos(window, width / 2, height / 2);
}

void Camera::move()
{
	float speed = 1;
	trnsfrm.rgdBdy.velocity = glm::vec3(); //reset velocity to avoid sliding
	rotMat = (glm::mat3)glm::yawPitchRoll(trnsfrm.rotation.y, trnsfrm.rotation.x, trnsfrm.rotation.z);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT))
		speed = 2;
	else
		speed = 1;

	if (glfwGetKey(window, GLFW_KEY_A)) 
		trnsfrm.rgdBdy.velocity += rotMat * glm::vec3(-4, 0, 0) * speed;
	if (glfwGetKey(window, GLFW_KEY_D))
		trnsfrm.rgdBdy.velocity += rotMat * glm::vec3(4, 0, 0) * speed;
	if (glfwGetKey(window, GLFW_KEY_W)) 
		trnsfrm.rgdBdy.velocity += rotMat * glm::vec3(0, 0, -4) * speed;
	if (glfwGetKey(window, GLFW_KEY_S)) 
		trnsfrm.rgdBdy.velocity += rotMat * glm::vec3(0, 0, 4) * speed;
	if (glfwGetKey(window, GLFW_KEY_SPACE))
		trnsfrm.location += glm::vec3(0, .01, 0);

	//float cDrag = -5;
	//trnsfrm.rgdBdy.force += cDrag * trnsfrm.rgdBdy.velocity;

	//float speed = 2.f;
	//if (trnsfrm.rgdBdy.velocity != glm::vec3()) { //if velocity isn't a zero vector
		//trnsfrm.rgdBdy.velocity = glm::normalize(trnsfrm.rgdBdy.velocity);
	//}

	//trnsfrm.location += trnsfrm.rgdBdy.velocity * Engine::GetDeltaTime();// *speed;
}


