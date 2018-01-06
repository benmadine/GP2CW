#include "GameManager.h"
#include "CameraManager.h"
#include <iostream>
#include <string>

unsigned int indices[] = { 0,1,2 };

///Summary <Transforms>
//Different transfroms for the different models
Transform transMonkey; 
Transform transPlayer;
Transform transBullet;


GameManager::GameManager()
{
	collision = false; //Sets the collision to false at the start
	gameStates = GameState::PLAYING; //Game state is made equal to playing

	GameDisplay* GameDispler = new GameDisplay();  //Game Display pointer

	AudioManager* audioDevice(); //Pointer to audio manager

#pragma region Meshes
	MeshManager* alienMesh[10]; //Alien mesh array
	MeshManager* playerMesh(); //Player mesh 
	MeshManager* bulletMesh(); //Bullet mesh
#pragma endregion

#pragma region Shaders
	ShaderManager* shader1(); //The Player
	ShaderManager* shader4(); //Fog
#pragma endregion

}

GameManager::~GameManager()
{
}

void GameManager::run()
{
	initialiseSystems(); //InitSys method
	loopingGame(); //Method that continues to loop the methods insdie it
}

void GameManager::initialiseSystems()
{
	gameDispler.initialiseDisplay(); //Initalise the display

	myCam.InitaliseCamera(glm::vec3(0, 0, -5), 70.0f, (float)gameDispler.getWidthX() / gameDispler.getHeightY(), 0.01f, 1000.0f); //Initalises the camera at the pos

#pragma region Sounds
	shooting = audioDevice.loadSound("..\\res\\Shooting.wav"); //Shooting sound

	backGroundMusic = audioDevice.loadSound("..\\res\\BackGround.wav"); //Background music noise

	alienDie = audioDevice.loadSound("..\\res\\AlienDie.wav"); //Alien die sound
#pragma endregion

#pragma region ShaderInfo
	shader1.initShader("..\\res\\shader"); //Shader info, shader used on the models
	shader4.initFogShader("..\\res\\Fog"); //Shader used for fog
#pragma endregion

#pragma region ModelLoading
	for (int i = 0; i < 10; i++)
	{
		alienMesh[i].modelLoader("..\\res\\AlienInvader.obj"); //Loading the alien model 10 times, one for every alien
	}

	playerLoaded = false; //Setting the player loaded to false

	playerMesh.modelLoader("..\\res\\AlienGiantBirdSubmit.obj"); //Loading the player model

	bulletMesh.modelLoader("..\\res\\apple textured obj.obj"); //Loading the bullet model from that file

#pragma endregion

	counter = 1.0f; //Setting the counter
}

void GameManager::loopingGame()
{
	while (gameStates != GameState::QUIT) //If the game states do not equal quit
	{
		inputProcess(); //Player input method

		drawingGame(); //Drawing game method
		for (int i = 0; i < 10; i++)
		{
			colliderChecker(bulletMesh.getSpherePosition(), bulletMesh.getSphereRadui(), alienMesh[i].getSpherePosition(), alienMesh[i].getSphereRadui()); // For the Bullet/Aliens

			alienCollision(playerMesh.getSpherePosition(), playerMesh.getSphereRadui(), alienMesh[i].getSpherePosition(), alienMesh[i].getSphereRadui()); // For the Player/Aliens
		}
		playAudio(backGroundMusic, myCam.getPos()); //Plays backgorund
	}
}

void GameManager::inputProcess()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) //get and process events
	{
		switch (event.type) //Swithc statement
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
#pragma region PlayerMovement
			case SDLK_a:
				PlayerMovement(0.5f, 0.0f); //Moves the player 0.5f right
				break;
			case SDLK_d:
				PlayerMovement(-0.5f, 0.0f); //Moves the player 0.5f left
				break;
			case SDLK_w:
				PlayerMovement(0.0f, 0.5f); //Moves the player 0.5f up
				break;
			case SDLK_s:
				PlayerMovement(0.0f, -0.5f); //Moves the player 0.5f down
				break;
			case SDLK_SPACE:
				bulletFired = true; //When the user presses space then the boolean is actiavtes, check draw method to see where it goes next
				break;
#pragma endregion
				
#pragma region CameraStuff
			case SDLK_LEFT:
				myCam.MoveLeft(1); //Moves the camera left
				break;
			case SDLK_RIGHT:
				myCam.MoveRight(1); //Moves camera right
				break;
			case SDLK_UP:
				myCam.MoveForward(1); //Zooms camera in
				break;
			case SDLK_DOWN:
				myCam.MoveBack(1); //Zooms camera out
				break;
#pragma endregion

			}	
			break;
			case SDL_QUIT:
				gameStates = GameState::QUIT;
				break;
		}
	}
}

void GameManager::playAudio(unsigned int Source, glm::vec3 pos) //Method used to play the audio
{
	ALint state;
	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	/*
	Possible values of state
	AL_INITIAL
	AL_STOPPED
	AL_PLAYING
	AL_PAUSED
	*/
	if (AL_PLAYING != state)
	{
		audioDevice.SoungPlay(Source, pos);
	}
} 

bool GameManager::colliderChecker(glm::vec3 m1Position, float m1Radius, glm::vec3 m2Position, float m2Radius) //Check if the two radius in proximity of each other
{
	float dist = glm::sqrt((m2Position.x - m1Position.x)*(m2Position.x - m1Position.x) + 
		(m2Position.y - m1Position.y)*(m2Position.y - m1Position.y) + 
		(m2Position.z - m1Position.z)*(m2Position.z - m1Position.z)); //Distance calcualtion to see if they are close enough

	if (dist < (m1Radius + m2Radius)) //If dist is less than radius then collision is true
	{
		bulletFired = false;
		collision = true;	
		audioDevice.ListenerSetting(myCam.getPos(), m1Position); //add bool to mesh
		playAudio(alienDie, m1Position);
		return true;
	}
	else //If not collision is false
	{
		return false;
	}

	return false;
}

bool GameManager::alienCollision(glm::vec3 m1Position, float m1Radius, glm::vec3 m2Position, float m2Radius) //Alien collision detection
{
	float dist = glm::sqrt((m2Position.x - m1Position.x)*(m2Position.x - m1Position.x) +
		(m2Position.y - m1Position.y)*(m2Position.y - m1Position.y) +
		(m2Position.z - m1Position.z)*(m2Position.z - m1Position.z)); //Distance varaible, same as the method abouve^^

	if (dist < (m1Radius + m2Radius)) //If distance is less than radius, collision is true
	{
		alienCollisioner = true;
		audioDevice.ListenerSetting(myCam.getPos(), m1Position); //add bool to mesh
		playAudio(alienDie, m1Position);
		return true;
	}
	else //Else collision is false
	{
		return false;
	}

	return false;
}

#pragma region PlayerControllers
void GameManager::BulletManager()
{
	TextureManager textures("..\\res\\AppleTexture.jpg"); //Applies appropriate texture to apple

	shader1.Bind(); //Binds the shader
	transBullet.SetPos(glm::vec3(transPlayer.GetPos()->x, transPlayer.GetPos()->y + 1 * 2, 10.0)); //Updates the bullet position
	transBullet.SetScale(glm::vec3(0.01, 0.01, 0.01)); //Sets the bullet scale

	shader1.Update(transBullet, myCam); //Updates bullet posiition
	if (transBullet.GetPos()->y >= transPlayer.GetPos()->y) //Makes sure the bullet continues to move
	{
		transBullet.SetPos(glm::vec3(transBullet.GetPos()->x, transBullet.GetPos()->y + counter, 10));
		shader1.Update(transBullet, myCam); //Updates the bullets position
	}

	textures.Binder(0); //Texture binder

	if (collision == false) //If collision is false then keep drawing and 
	{
		bulletMesh.Drawing(); //Draws bullet
		playAudio(shooting, glm::vec3(transPlayer.GetPos()->x, transPlayer.GetPos()->y, transBullet.GetPos()->z)); //Plays the audio and sets its position
	}

	bulletMesh.sphereDataUpdate(*transBullet.GetPos(), 0.5f); //Updates the sphere position
}

void GameManager::PlayerMovement(float i, float k)
{
	transPlayer.SetPos(glm::vec3(transPlayer.GetPos()->x + i, transPlayer.GetPos()->y + k, 10.0)); //Moves the player, used in the input process method
	//X coordinate Stuff
	if (transPlayer.GetPos()->x >= 10) //If the player goes to boundry then teleports them to other side of screen
		transPlayer.SetPos(glm::vec3(-9.9, transPlayer.GetPos()->y, 10.0));
	if (transPlayer.GetPos()->x <= -10)
		transPlayer.SetPos(glm::vec3(9.9, transPlayer.GetPos()->y, 10.0));
	//Y Coordincate Stuff
	if (transPlayer.GetPos()->y >= 10) //If the player goes to boundry then teleports them to other side of screen
		transPlayer.SetPos(glm::vec3(transPlayer.GetPos()->x, -9.9, 10.0));
	if (transPlayer.GetPos()->y <= -10)
		transPlayer.SetPos(glm::vec3(transPlayer.GetPos()->x, 9.9, 10.0));
}

void GameManager::PlayerManager()
{
	TextureManager textures("..\\res\\BirdTexture.jpg"); //Applies the bird texture

	if (!playerLoaded) //If the player has loaded then dont keep set the position
	{
		transPlayer.SetPos(glm::vec3(0, -7, 10.0)); //Set player posiiton
		transPlayer.SetScale(glm::vec3(0.3, 0.3, 0.3)); //Set player scale
	}
	playerLoaded = true; //Player loaded is true
	transPlayer.SetRot(glm::vec3(0, counter * 100, 0)); //continually roates the player
	inputProcess(); //Calls the input process method
	shader1.Bind(); //Binds the shader
	shader1.Update(transPlayer, myCam); //Updates the player position
	textures.Binder(0);
	if (alienCollisioner == false) //Checks collision so model keeps loading
	{
		playerMesh.Drawing();
	}
	playerMesh.sphereDataUpdate(*transPlayer.GetPos(), 0.4f); //Updates shader position
}
#pragma endregion

void GameManager::AlienManager()
{
	TextureManager alienTextures[4] = { "..\\res\\AlienShader.jpg" , "..\\res\\AlienShaderBlue.jpg" ,
		"..\\res\\AlienShaderPink.jpg" , "..\\res\\AlienShaderRed.jpg" }; //Multiple alien textures
	for (int i = 0; i < 10; i++) //For loop for all different alines
	{
		shader1.Bind(); //Binds the shader

		transMonkey.SetPos(glm::vec3((rand() % -15 - 8), (rand()%-6 + 1), 10.0)); //Sets a random x and y position
		transMonkey.SetScale(glm::vec3(0.1, 0.1, 0.1));
		transMonkey.SetRot(glm::vec3((rand() %6+1), 0, 0)); //Gives a random rotation
		
		alienMesh[i].sphereDataUpdate(*transMonkey.GetPos(), 0.62f); //Updates the collider

		shader1.Update(transMonkey, myCam); //Updates postion
		alienTextures[rand() % 4].Binder(0); //Binds a random texture

		if (collision == false || alienCollisioner == false) //Checks if the collision
		{
			alienMesh[i].Drawing();
		}
		
	}
}

void GameManager::drawingGame()
{ 
	gameDispler.displayClearer(0.0f, 0.0f, 0.0f, 0.0f);

	//TextureManager TextureSkyBox("..\\res\\Skybox.jpg");

	shader4.Bind(); //Binds the shader

	AlienManager(); //Calls the alien managaer method

	PlayerManager(); //Calls the player manager method

	if (bulletFired) //Checks if the bullet has been fired, if so then call bullet manager method
	{
		BulletManager();
	}

	counter = counter + 0.01f; //Adds to the counter

	glEnableClientState(GL_COLOR_ARRAY); 
	glEnd();

	gameDispler.bufferSwitch(); //Swaps the buffer
}
