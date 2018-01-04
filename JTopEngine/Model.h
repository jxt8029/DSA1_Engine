#include <FreeImage.h>

#include <GL\glew.h>    //
#include <GLFW\glfw3.h> //don't switch the order of these two

#include <glm\glm.hpp>

#include <vector>

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#pragma once
class Model
{
private:
	GLuint vertArr;
	GLuint vertBuf;
public:
	unsigned int vertCount;
	Model();
	~Model();
	bool buffer(std::string objFile);
	void render();
};

struct Vertex {
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};

struct vertInd {
	unsigned int locInd;
	unsigned int uvInd;
	unsigned int normInd;
};

