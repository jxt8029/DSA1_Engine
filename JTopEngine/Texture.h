#include <FreeImage.h>
#include <GL\glew.h>    
#include <GLFW\glfw3.h> 
#include <glm\glm.hpp>

#include <iostream>
#pragma once
class Texture
{
public:
	char* filename;
	unsigned int texID;
	void use();
	void load();
	void unload();
	Texture(char* file);
	~Texture();
};

