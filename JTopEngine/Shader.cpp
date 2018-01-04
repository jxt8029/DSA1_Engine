#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::load()
{
	//compile shaders
	bool resultv = compile(GL_VERTEX_SHADER);
	bool resultf = compile(GL_FRAGMENT_SHADER);
	if (!resultv || !resultf) {
		return false;
	}

	//attach and link shaders to program
	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);

	//check if link was successful
	GLint result;
	glGetProgramiv(program, GL_LINK_STATUS, &result);

	if (!result) {
		GLint length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
		GLchar* infoLog = new GLchar[length];
		glGetProgramInfoLog(program, length, 0, infoLog);
		printf(infoLog);
		delete[] infoLog;
		return false;
	}
	else {
		return true;
	}
}

bool Shader::compile(GLenum shaderType)
{
	char* bytes;

	//vertex shader
	if (shaderType == GL_VERTEX_SHADER) {
		bytes = readBinaryFile(filenamev);
	}
	//fragment shader
	else { 
		bytes = readBinaryFile(filenamef);
	}
	//error opening file
	if (bytes == nullptr) {
		printf("Error opening file.");
		return 0;
	}

	//create and compile shader
	GLuint index = glCreateShader(shaderType);

	glShaderSource(index, 1, &bytes, 0);

	glCompileShader(index);

	delete[] bytes;

	//check if successful
	GLint result;
	glGetShaderiv(index, GL_COMPILE_STATUS, &result);

	if (!result) {
		GLint length;
		glGetShaderiv(index, GL_INFO_LOG_LENGTH, &length);
		GLchar* infoLog = new GLchar[length];
		glGetShaderInfoLog(index, length, 0, infoLog);
		printf(infoLog);
		delete[] infoLog;
		glDeleteShader(index);
		return false;
	}
	else {
		//set class variables equal to read in data
		if (shaderType == GL_VERTEX_SHADER) {
			vprogram = index;
		}
		else {
			fprogram = index;
		}
		return true;
	}
}

//read in file and store data in character array
char * Shader::readBinaryFile(std::string filename)
{
	std::ifstream instream(filename, std::ios::binary);

	if (!instream.is_open()) return nullptr;

	//get length of file
	instream.seekg(0, std::ios::end);                  //go to end of file
	int length = instream.tellg();                     //gets file length
	instream.seekg(0, std::ios::beg);                  //go to beginning

													   //read all of it at once
	char* bytes = new char[length + 1];
	bytes[length] = '\0';
	instream.read(bytes, length);                      //read to where, number of bytes

	instream.close();

	return bytes;
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);
	vprogram = 0;
	fprogram = 0;
	program = 0;
}
