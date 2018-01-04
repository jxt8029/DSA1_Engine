#include <FreeImage.h>

#include <GL\glew.h>   
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <string>
#include <iostream>
#include <fstream>

#pragma once
class Shader
{
public:
	GLuint program, vprogram, fprogram;
	std::string filenamev = "shaders/vShader.glsl";
	std::string filenamef = "shaders/fShader.glsl";
	Shader();
	~Shader();
	bool load(); //loads shaders
	bool compile(GLenum shaderType); //read and compile shader files
	char* readBinaryFile(std::string filename); //helper function for compile
	void use(); //function wrapper
	void unload(); //deallocate shader memory from graphics card
};

