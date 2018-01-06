#pragma once
//Includes
#include <SDL/SDL.h>
#include <GL\glew.h>
#include <iostream>
#include <string>
using namespace std;


class GameDisplay
{
public:

	GameDisplay(); //Constructor
	~GameDisplay(); //Deconstructor

	void initialiseDisplay(); //Method for initialising the display
	void bufferSwitch(); //swapping out the buffers
	void displayClearer(float r, float g, float b, float a); //Clears the display

	float getWidthX(); //Width of screen
	float getHeightY(); //Height of screen

private:

	void returnError(std::string errorString);

	SDL_Window* gameWindow; //window pointer
	SDL_GLContext contextGLer; //varaible to hold context

	int widthScreenX; //Screen width
	int heightScreenY; //Screen height
};

