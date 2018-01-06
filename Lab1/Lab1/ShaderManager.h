#pragma once
//Include
#include <string>
#include <GL\glew.h>
#include "TransformManager.h"
#include "CameraManager.h"

class ShaderManager //Shader class
{
public:
	ShaderManager() {} //Shader Constructor
	
	void initShader(const std::string& filename); //Initalise shader method, take in a string which is the file name

	void initFogShader(const std::string& filename);

	void Bind(); //Set gpu to use our shaders
	void Update(const Transform& transform, const CameraManager& camera); //Update method takes in two arguments: the transform of the shader and the camera

	std::string ShaderManager::ShaderLoader(const std::string& fileName); //Loading the shader, using a string which is the file name
	void ShaderManager::ShaderTroubleShoot(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage); //Checking if their is an error in the shader, using a Check Shader Error method
	GLuint ShaderManager::ShaderCreation(const std::string& text, unsigned int type); //Creates the shader method

	~ShaderManager(); //destructor


protected:
private:
	static const unsigned int NUM_SHADERS = 4; // numb2r of shaders

	enum //Enumerators
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	GLuint programFog;
	GLuint program; // Track the shader program
	GLuint shaders[NUM_SHADERS]; //array of shaders
	GLuint uniforms[NUM_UNIFORMS]; //no of uniform variables
};