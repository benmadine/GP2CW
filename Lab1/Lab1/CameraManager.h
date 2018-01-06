#pragma once
//Includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct CameraManager //Data structure
{
public:
	CameraManager() //Constructor
	{

	} 

	///Summary<InitaliseCamera>
	//Takes in four seperate arguments: vector position, float field of view, float aspect ration and float of the far and near clipping planes
	///Summary
	void InitaliseCamera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar) 
	{
		this->pos = pos; //Variable position 
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f); //Forward vector
		this->up = glm::vec3(0.0f, 1.0f, 0.0f); //Up vectors
		this->projection = glm::perspective(fov, aspect, zNear, zFar); //Cameras projection which containts: field of biew, aspect ratio, near and far clipping planes
		
	}

	inline glm::mat4 GetViewProjection() const //Where the camera is looking at method
	{
		/*Returns the sum of: */ return projection * glm::lookAt(pos, pos + forward, up); 
	}

	glm::vec3 getPos() //Getting the camera position
	{
		return this->pos; //Returns that position
	}

#pragma region Camera Movement Controls
	void MoveForward(float amout) //Moving the camera forward
	{
		pos += forward * amout; //Adds the position to the current camera positon
	}

	void MoveBack(float amout) //Moving the camera backs
	{
		pos -= forward * amout; //Takes the position away from the current camera position
	}

	void MoveLeft(float amout) //Moving the camera left
	{
		pos -= glm::cross(up, forward) * amout; //Uses the cross key word so the camera will move to the left by taking the value away from the current position
	}

	void MoveRight(float amout) //Moving Camera Right
	{
		pos += glm::cross(up, forward) * amout; //Uses the cross key word so that the camera will move to right by adding the value from the current position
	}
#pragma endregion

protected:
private:
	glm::mat4 projection; //Matrix Varaible

#pragma region Vector 3 Varaibles
	glm::vec3 pos;
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 rotation;
#pragma endregion

};
