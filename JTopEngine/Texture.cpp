#include "Texture.h"



void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, texID);
}

void Texture::load()
{
	//1. use FreeImage to read from hard drive
	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(filename, 0), filename);

	if (image == nullptr) { //load failed
		printf("Texture load failed");
		return;
	}

	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image); //convert to 32 bit bmp
	FreeImage_Unload(image);                                 //done using image, so unload

	//2. generate and bind texID
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);

	//3. upload
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, FreeImage_GetWidth(image32Bit),
		FreeImage_GetHeight(image32Bit), 0, GL_BGRA, GL_UNSIGNED_BYTE,
		(void*)FreeImage_GetBits(image32Bit));

	//4. set filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//5. unload with FreeImage
	FreeImage_Unload(image32Bit);
	glBindTexture(GL_TEXTURE_2D, 0); //unbind texture
}

void Texture::unload()
{
	glDeleteTextures(1, &texID);
}

Texture::Texture(char* file)
{
	filename = file;
}


Texture::~Texture()
{
}
