//include with < > : external library, not in project directory (we didn't make it)
#include <iostream>
#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>
#include <glm\gtx\transform.hpp>
//glm\gtx\euler_angles.hpp and glm\gtx\transform.hpp are already in from Camera.h

#include <vector>

#include "Engine.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Object.h"

int main() {

	Engine engine;
	if (engine.load() == -1) {
		return 0;
	}

	//Model model;
	//model.buffer("models/greataxe.obj"); //load model
	Texture texture("textures/space.jpg");
	Texture texture2("textures/rock4.jpg");
	Texture texture3("textures/rock.jpg");
	texture.load();
	texture2.load();
	texture3.load();
	texture.use();
	std::string str = texture.filename;
	Model models[] = {
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model(),
		Model()
	};
	
	models[0].buffer("models/greataxe.obj");
	models[1].buffer("models/box.obj");
	for (int i = 2; i < sizeof(models) / sizeof(*models) - 1; i++) {
		models[i].buffer("models/sphere.obj");
	}

	float randLoc[30];
	srand((unsigned int)time(0));
	for (int i = 0; i < 30; i++) {
		randLoc[i] = rand() % 80 - 40;
	}

	float randScl[10];
	for (int i = 0; i < 10; i++) {
		randScl[i] = rand() % 8 - 1.5f;
	}

	Object objs[] = { 
		Object(&Transform(
			glm::vec3(5, 0, -2),          //location
			glm::vec3(90, 90, 0),          //rotation
			glm::vec3(1, 1, 1),    //scale
			RigidBody(
				glm::vec3(0, 0, 0),		 //velocity                       
				glm::vec3(0, 0, 0),      //force
				1)),                     //mass
			&str,
			Object::aabb),
		Object(&Transform(
		glm::vec3(0, 0, 0),          //location
		glm::vec3(0, 0, 0),          //rotation
		glm::vec3(300, 300, 300),    //scale
		RigidBody(
			glm::vec3(0, 0, 0),		 //velocity                       
			glm::vec3(0, 0, 0),      //force
			1)),                     //mass
		&str,
		Object::aabb),    //texture filename / collider
		Object(&Transform(
			glm::vec3(randLoc[0], randLoc[1], randLoc[2]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[0], randScl[0], randScl[0]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[3], randLoc[4], randLoc[5]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[1], randScl[1], randScl[1]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[6], randLoc[7], randLoc[8]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[2], randScl[2], randScl[2]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[9], randLoc[10], randLoc[11]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[3], randScl[3], randScl[3]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[12], randLoc[13], randLoc[14]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[4], randScl[4], randScl[4]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[15], randLoc[16], randLoc[17]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[5], randScl[5], randScl[5]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[18], randLoc[19], randLoc[20]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[6], randScl[6], randScl[6]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[21], randLoc[22], randLoc[23]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[7], randScl[7], randScl[7]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[24], randLoc[25], randLoc[26]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[8], randScl[8], randScl[8]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere),
		Object(&Transform(
			glm::vec3(randLoc[27], randLoc[28], randLoc[29]),
			glm::vec3(0, 0, 0),
			glm::vec3(randScl[9], randScl[9], randScl[9]),
			RigidBody(
				glm::vec3(0, 0, 0),
				glm::vec3(0, 0, 0),
				1)),
			&str,
			Object::sphere)
	};
	
	Shader shader; 
	if (shader.load()) { //attempt to load and use shader
		shader.use();
	}

	Camera camera;
	camera.camLoc += glm::vec3(1, 0, 1);
	camera.start(); //initialize camera information

	//initialize time
	Engine::t = (float)glfwGetTime();
	
	//close on escape
	while (!glfwGetKey(engine.GLFWwindowPtr, GLFW_KEY_ESCAPE)) {
		//Game Loop
		glfwPollEvents();

		Engine::UpdateTime();

		//Clear the canvas
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Update camera information
		camera.turn();
		camera.move();
		camera.upload();
		camera.trnsfrm.AddGravity();
		camera.trnsfrm.UpdateVelocity();
		//printf("%f", camera.trnsfrm.location.y);

		int objsLength = sizeof(objs) / sizeof(*objs);
		for (int i = 0; i < objsLength; i++) {
			glm::mat4 scale = glm::scale(objs[i].trnsfrm->scale);
			glm::mat4 rotation = glm::yawPitchRoll(objs[i].trnsfrm->rotation.y,
				objs[i].trnsfrm->rotation.x, objs[i].trnsfrm->rotation.z);
			glm::mat4 location = glm::translate(objs[i].trnsfrm->location);

			objs[1].trnsfrm->location = camera.trnsfrm.location;

			objs[i].trnsfrm->AddGravity();
			if(i != 1)
				objs[i].trnsfrm->rotation.y += .001;
			
			/*
			if (objs[i].trnsfrm->location.y < -10) {
					objs[i].trnsfrm->AddNormal();
			}
			
			objs[i].trnsfrm->UpdateVelocity();*/

			if (Engine::CollidesWith(&objs[i], &camera.object)) {
				if(i != 0)
					objs[i].trnsfrm->location = glm::vec3(1000, 0, 0);
			}
			if (Engine::CollidesWith(&camera.object, &objs[0])) {
				camera.trnsfrm.location = glm::vec3();
			}

			/*if (glfwGetKey(engine.GLFWwindowPtr, GLFW_KEY_LEFT))
				objs[1].trnsfrm->rgdBdy.velocity += glm::vec3(-4, 0, 0);
			if (glfwGetKey(engine.GLFWwindowPtr, GLFW_KEY_RIGHT))
				objs[1].trnsfrm->rgdBdy.velocity += glm::vec3(4, 0, 0);*/

			objs[i].trnsfrm->UpdateVelocity();
			objs[i].trnsfrm->objWorldTrnsfrmMtx = location * rotation * scale;
			glUniformMatrix4fv(7, 1, GL_FALSE, &objs[i].trnsfrm->objWorldTrnsfrmMtx[0][0]);
			
			if (i == 0) {
				texture3.use();
			}
			else if (i == 1) {
				texture.use();
			}
			else {
				texture2.use();
			}
			models[i].render();
		}
		//model.render(); //draw the model

		//Swap the front (what the screen displays) and back (what OpenGL draws to) buffers
		glfwSwapBuffers(engine.GLFWwindowPtr);
	}

	texture.unload();
	texture2.unload();
	shader.unload();
	glfwTerminate();
	return 0;
}