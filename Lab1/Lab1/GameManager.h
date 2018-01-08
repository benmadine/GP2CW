#pragma once

#pragma region Includes
#include <SDL\SDL.h>
#include <GL/glew.h>
#include <vector>
#include <list>
#include <cstdlib>
#include "GameDisplay.h" 
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "TransformManager.h"
#include "AudioManager.h"
#pragma endregion




enum class GameState{PLAYING, QUIT}; //Different game states, in playing the game is running, when in quit then the application closes

class GameManager
{
public:
	GameManager(); //Constructor
	~GameManager(); //Deconstructor

	void run(); //Run method

private:

	void initialiseSystems(); //Initialise's the game and start running a few methods (gameManagaer.cpp)s
	void inputProcess(); //PLayers input keys
	void loopingGame(); //Loops some of the methods so the game keepings running
	void drawingGame(); //Drawing game method

	void playAudio(unsigned int Source, glm::vec3 pos); 

	void PlayerManager(); //Player Methods
	void PlayerMovement(float i, float k); //Player movement method, takes in two arguments

	void AlienManager(); //AlienMethod

	void BulletManager(); //Bullet Method

	void SkyBoxMethod(); //SkyBoxDrawMethod

	bool colliderChecker(glm::vec3 m1Position, float m1Radius, glm::vec3 m2Position, float m2Radius); //For Bullet/Alien

	bool alienCollision(glm::vec3 m1Position, float m1Radius, glm::vec3 m2Position, float m2Radius); //For Player/Alien

	GameDisplay gameDispler; //Game Display Variable
	GameState gameStates; //The game states

	MeshManager alienMesh[10]; //The different aliens, need to be array to hold all ten of them
	
	MeshManager playerMesh; //player mesh
	MeshManager bulletMesh; // Bullet mesh

	TextureManager textures; //Different textures being used
	TextureManager skyTexture[6]; //Sky box texture
	TextureManager alienTextures[4]; //Different alien texutres, four for the four different varients

	ShaderManager shader1; //Players
	ShaderManager shader4; //Fog

	CameraManager myCam; //camera varaible, how it access the camera class

	float counter; //Counter float
	float skyBoxSize = 65; //Sky box size

	bool playerLoaded; //Played loaded boolean, just a check
	bool collision; //Collision bool to see if collision is true
	bool alienCollisioner; //Collision checker but for aliens 
	bool bulletFired; //Checks if the alien has been collided with

	vector<MeshManager*> bulletList; //Bullet list, to hold multiple bullets

	AudioManager audioDevice; //Audio device
	unsigned int shooting; //Shooting sound 
	unsigned int backGroundMusic; //Backgorund music sound
	unsigned int alienDie; //Alien Die Sound
	
};

