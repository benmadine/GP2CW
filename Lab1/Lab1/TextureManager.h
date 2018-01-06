#pragma once
//Includes
#include <string>
#include <GL\glew.h>
#include <SOIL\SOIL.h>


class TextureManager //Texture Manager Class
{
public:
	TextureManager() {}; //Constructor

	TextureManager(const std::string& fileTitle); //TextureManager method, taking in a string argument whihc is the name of the texture file

	void TextureSkyBox(const std::string& fileTitle); //Creating the sky box method

	void Binder(unsigned int unit); // Binder method, which is used to bind the textures

	~TextureManager(); //destructor
	


protected:
private:
	GLuint textureController; //GL variable
	
};

