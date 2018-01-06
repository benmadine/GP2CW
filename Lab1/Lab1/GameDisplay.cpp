#include "GameDisplay.h"


GameDisplay::GameDisplay()
{
	gameWindow = nullptr; //initialise to generate null access violation for debugging. 
	widthScreenX = 1024.0f; //Sets the screen width
	heightScreenY = 768.0f;  //Sets the screen heigt
}

GameDisplay::~GameDisplay()
{
	SDL_GL_DeleteContext(contextGLer); // delete context
	SDL_DestroyWindow(gameWindow); // detete window (make sure to delete the context and the window in the opposite order of creation in initDisplay())
	SDL_Quit(); //Quits the game
}

///Summary<>
//Getters used to return the width and height of the screen
float GameDisplay::getWidthX() { return widthScreenX; } 
float GameDisplay::getHeightY() { return heightScreenY; }

void GameDisplay::returnError(std::string errorString) //Errror check, returs a messgae to the console
{
	std::cout << errorString << std::endl;
	std::cout << "press any  key to quit...";
	int in;
	std::cin >> in;
	SDL_Quit();
}

void GameDisplay::bufferSwitch()
{
	SDL_GL_SwapWindow(gameWindow); //swap buffers
}

void GameDisplay::initialiseDisplay()
{
	SDL_Init(SDL_INIT_EVERYTHING); //initalise everything

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); //Min no of bits used to diplay colour
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // set up double buffer   

	gameWindow = SDL_CreateWindow("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		(int)widthScreenX, (int)heightScreenY, SDL_WINDOW_OPENGL); // create window

	if (gameWindow == nullptr) //If the window isnt existing
	{
		returnError("window failed to create"); //Returns a messgae to the window 
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(gameWindow);

	if (glContext == nullptr) //If the context is created returns error
	{
		returnError("SDL_GL context failed to create");
	}

	GLenum error = glewInit();
	if (error != GLEW_OK) //Checks if the the glew varaible isnt initialised
	{
		returnError("GLEW failed to initialise");
	}

	glEnable(GL_DEPTH_TEST); 
	glEnable(GL_CULL_FACE);

	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
}

void GameDisplay::displayClearer(float r, float g, float b, float a) //Clears the display
{
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}