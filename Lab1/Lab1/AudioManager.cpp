#include "AudioManager.h"


AudioManager::AudioManager() //Constructor
{
	device = alcOpenDevice(NULL); //open sound card
	if (device == NULL) //If the device is non existant 
	{
		std::cout << "cannot open sound card" << std::endl; // Message displayed to the console
	}

	context = alcCreateContext(device, NULL); 

	if (context == NULL) //If the context is non existant
	{
		std::cout << "cannot open context" << std::endl; // Message displayed to the console
	}

	alcMakeContextCurrent(context);
}

AudioManager::~AudioManager() //Destructor
{
	for (unsigned int i = 0; i < datas.size(); i++) //For loop for the size of data
	{
		alDeleteSources(1, (unsigned int*)&datas[i].sourceID);
		if (datas[i].bufferID != -1) //Checking if the buffer does not equal -1
		{
			alDeleteBuffers(1, (unsigned int*)&datas[i].bufferID); //Delete the buffers
			delete[] datas[i].buffer;
		}
	}
	alcDestroyContext(context); //Closes the context
	alcCloseDevice(device); //Closes the device
}

bool AudioManager::isBigEndian() //Used to read the sound data properly
{
	int a = 1;
	return !((char*)&a)[0];
}

int AudioManager::convertToInt(char* buffer, int length) // Converts a char array to int array as openAl only uses ints as its parameters
{
	int a = 0;
	if (!isBigEndian())
		for (int i = 0; i < length; i++)
			((char*)&a)[i] = buffer[i];
	else
		for (int i = 0; i < length; i++)
			((char*)&a)[3 - i] = buffer[i];
	return a;
}

char* AudioManager::loadWAV(const char* fn, int& chan, int& samplerate, int& bps, int& size) //Loads the wav file and allows it to be read
{
	char buffer[4];
	std::ifstream in(fn, std::ios::binary);

#pragma region BufferReading
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	chan = convertToInt(buffer, 2);
	in.read(buffer, 4);
	samplerate = convertToInt(buffer, 4);
	in.read(buffer, 4);
	in.read(buffer, 2);
	in.read(buffer, 2);
	bps = convertToInt(buffer, 2);
	in.read(buffer, 4);
	in.read(buffer, 4);
	size = convertToInt(buffer, 4);
#pragma endregion

	char* soundData = new char[size];
	in.read(soundData, size);
	return soundData; //Returns the sound data character
}

unsigned int AudioManager::loadSound(const char* filename) //Loads the sound file
{
	bool found = false; //Setting the boolean to false
	unsigned int sourceID, bufferID; //Creating two ints 
	char* soundData = NULL;
	for (unsigned int i = 0; i < datas.size(); i++) //For loop for the size of the data
	{
		if (datas[i].name == filename && datas[i].bufferID != -1)
		{
			bufferID = datas[i].bufferID;
			found = true; //found is equal to true
			break;
		}
	}
	if (!found) //If found is false
	{
		int channel, sampleRate, bps, size;
		soundData = loadWAV(filename, channel, sampleRate, bps, size);
		unsigned int format;
		alGenBuffers(1, &bufferID);

		if (channel == 1)
		{
			if (bps == 8)
			{
				format = AL_FORMAT_MONO8;
			}
			else
			{
				format = AL_FORMAT_MONO16;
			}
		}
		else
		{
			if (bps == 8)
			{
				format = AL_FORMAT_STEREO8;
			}
			else
			{
				format = AL_FORMAT_STEREO16;
			}

		}

		alBufferData(bufferID, format, soundData, size, sampleRate);
	}
	alGenSources(1, &sourceID);
	alSourcei(sourceID, AL_BUFFER, bufferID);
	alSourcef(sourceID, AL_REFERENCE_DISTANCE, 1.0f);
	datas.push_back(data(sourceID, (!found ? bufferID : -1), soundData, filename));
	return sourceID;
}

void AudioManager::deleteSound(unsigned int id) //Deletes the sound file
{}

void AudioManager::SoungPlay(unsigned int id) //Plays the sound file
{
	alSourcePlay(id);
}
void AudioManager::SoungPlay(unsigned int id, glm::vec3& pos) //Plays the sound file
{
	alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
	alSourcePlay(id); //Playing the sound with the corretc id
}
void AudioManager::SoundStop(unsigned int id) //Stop the sound
{
	alSourceStop(id);
}
void AudioManager::ListenerSetting(glm::vec3& pos, glm::vec3& camLookAt) //Adds a listener to the screen and faces it towards the camera
{
	alListener3f(AL_POSITION, pos.x, pos.y, -pos.z);
	float orinet[6] = { camLookAt.x,camLookAt.y,camLookAt.z,0,1,0 }; //Looking at the camera
	alListenerfv(AL_ORIENTATION, orinet);
}