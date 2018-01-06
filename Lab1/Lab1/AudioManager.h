#pragma once
//Includes that the Audio Manager Class uses
#include <glm\glm.hpp>
#include <AL\al.h>
#include <AL\alc.h>
#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>
#include <glm/gtc/type_ptr.hpp>

class AudioManager //Audio Manager Class
{
	struct data //Data structure
	{
		int sourceID, bufferID; //The souce and buffer ID stored as and INT
		char* buffer; //Character varaible with pointer, named buffer
		std::string name; //String varaible called name
		data(unsigned int sI, unsigned int bI, char* b, const char* n) //Data varaiable taking in 4 arguments
		{
			this->sourceID = sI;
			this->bufferID = bI;
			this->buffer = b;
			this->name = n;
		}

	};

	struct Vector3 //Vector data structure 
	{
		float x, y, z; //x y and z floats
	};
	 
	std::vector<data> datas; // Vector data list
	ALCcontext* context; //Context Varaible
	ALCdevice *device; //Device varaible
	bool isBigEndian(); //Boolean varaible
	int convertToInt(char* buffer, int length); //Conersion method
	char* loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size); //Loading the wav sound file method

public:
	AudioManager(); //Constructor
	~AudioManager(); //Deconstructor 

#pragma region Sound Methods
	unsigned int loadSound(const char* filename);
	void deleteSound(unsigned int id);
	void SoungPlay(unsigned int id);
	void SoungPlay(unsigned int id, glm::vec3& pos);
	void SoundStop(unsigned int id);
	void ListenerSetting(glm::vec3& pos, glm::vec3& camLookAt);
#pragma endregion

private:

};

