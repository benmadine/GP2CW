#include "TextureManager.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
#include <vector>


TextureManager::TextureManager(const std::string& fileTitle)
{
	int widthX, heightY, numComp;
	unsigned char* imageInfo = stbi_load((fileTitle).c_str(), &widthX, &heightY, &numComp, 4);

	if (imageInfo == NULL)
		std::cerr << "Texture failed to load :( " << fileTitle << std::endl; //If the texture is failed to load

	glGenTextures(1, &textureController);
	glBindTexture(GL_TEXTURE_2D, textureController);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // wrap texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // wrap texture outside height

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // linear filtering for minification (texture is smaller than area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // linear filtering for magnifcation (texture is larger)

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthX, heightY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageInfo); //Target, Mipmapping Level, Pixel Format, Width, Height, Border Size, Input Format, Data Type of Texture, Image Data

	stbi_image_free(imageInfo);
}

void TextureManager::TextureSkyBox(const std::string& fileTitle)
{
	//GLuint textureCon;

	//int widthX, heightY;
	//unsigned char* imageInfo;

	//std::vector<int> faces;
	//faces.size == 6;
	////faces = { 0,1,2,3,4,5,6 };
	////faces.push_back(6);
	//////const std::size_t amount = 6;
	////faces.size = amount;

	//glBindTexture(GL_TEXTURE_CUBE_MAP, textureCon);

	//for (GLuint i = 0; i < faces.size(); i++)
	//{
	//	imageInfo = SOIL_load_image(faces[i], &widthX, &heightY, 0, SOIL_LOAD_RGB);
	//	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, widthX, heightY, 0, GL_RGB, GL_UNSIGNED_BYTE, imageInfo);
	//}
}

TextureManager::~TextureManager()
{
	glDeleteTextures(1, &textureController);
}

void TextureManager::Binder(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, textureController);
}
