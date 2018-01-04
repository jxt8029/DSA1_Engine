#include "Model.h"

Model::Model()
{
	vertArr = 0;
	vertBuf = 0;
}


Model::~Model()
{
}

bool Model::buffer(std::string objFile)
{
	std::vector<glm::vec3> locations;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<vertInd> vertInds;

	//open the .obj file
	std::ifstream instream(objFile, std::ios::in);

	if (!instream.is_open()) return false;

	std::string line;

	//read line by line
	while (std::getline(instream, line)) { 
		std::istringstream ss(line);
		std::string label;
		float f1, f2, f3;
		unsigned int i1, i2, i3;
		char slash;
		ss >> label; //determine what type of information is on that line

		//locations - v # # # format
		if (label == "v") {
			ss >> f1 >> f2 >> f3;
			locations.push_back(glm::vec3(f1, f2, f3));
		}

		//uvs - vt # # format
		else if (label == "vt") {
			ss >> f1 >> f2;
			uvs.push_back(glm::vec2(f1, f2));
		}

		//normals - vn # # # format
		else if (label == "vn") {
			ss >> f1 >> f2 >> f3;
			normals.push_back(glm::vec3(f1, f2, f3));
		}

		//faces - f #/#/# #/#/# #/#/# format
		else if (label == "f") {
			for (int i = 0; i < 3; i++) {
				ss >> i1 >> slash >> i2 >> slash >> i3;
				i1 -= 1;
				i2 -= 1;
				i3 -= 1;
				vertInds.push_back(vertInd{ i1, i2, i3 });
			}
		}

		//not used yet, will keep for future model loading
		else if (label == "s") {
			printf("Label: s\n");
		}
		else {
			//to make sure there isn't a problem with the .obj files
			printf("Invalid line.\n");
		}
	}
	instream.close();

	//fill vertex buffer data with vertices containing locations, uvs, and normals
	vertCount = vertInds.size();
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++){
		vertBufData[i] = {
			locations[vertInds[i].locInd],
			uvs[vertInds[i].uvInd],
			normals[vertInds[i].normInd]
		};
	}

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER,         //Where to copy to
		sizeof(Vertex) * vertCount,       //# of bytes to copy
		&vertBufData[0],                  //Where to copy from
		GL_STATIC_DRAW);                  //"hint" to OpenGL

	//locations
	glEnableVertexAttribArray(2); //Attribute index - 2

	glVertexAttribPointer(
		2,                  //Attribute index - 2 in this case
		3,                  //Number of components (x, y, z)
		GL_FLOAT,           //Type of data
		GL_FALSE,           //Should we normalize the data?
		sizeof(Vertex),     //Stride (Bytes per vertex)
		0);                 //Offset to this attribute

	//uvs
	glEnableVertexAttribArray(3); 

	glVertexAttribPointer(
		3,						 
		2,						 
		GL_FLOAT,				
		GL_FALSE,				 
		sizeof(Vertex),           
		(void*)sizeof(glm::vec3)); 

	//normals
	glEnableVertexAttribArray(4); 

	glVertexAttribPointer(
		4,								 
		3,								 
		GL_FLOAT,						
		GL_FALSE,									
		sizeof(Vertex),									
		(void*)(sizeof(glm::vec3) + sizeof(glm::vec2)));

	glBindVertexArray(0);
	return true;
}

void Model::render()
{
	//Render game objects
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
	//Unbind an object after drawing it
}
