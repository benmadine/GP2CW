#pragma once
//Includes
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "CameraManager.h"

struct Transform //Transform data structure
{
public:
	Transform(const glm::vec3& position = glm::vec3(), const glm::vec3& rotation = glm::vec3(), const glm::vec3& scaler = glm::vec3(1.0f, 1.0f, 1.0f)) //Transfom method which take in an argument for each of the variables: position, rotation and scaler
	{
		///Summary<Transform>
		//The varaibles which are in the method are equal to the actual class varaibles
		this->position = position;
		this->rotation = rotation;
		this->scaler = scaler;
	}

	inline glm::mat4 GetModel() const //runs as compile time, matrix
	{
		glm::mat4 posMat = glm::translate(position);
		glm::mat4 scaleMat = glm::scale(scaler);
		glm::mat4 rotX = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
		glm::mat4 rotY = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
		glm::mat4 rotZ = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
		glm::mat4 rotMat = rotX * rotY * rotZ;

		return posMat * rotMat * scaleMat;
	}
	
	///Summary<>
	//Getters for the position, rotation and scale 
	inline glm::vec3* GetPos() { return &position; } 
	inline glm::vec3* GetRot() { return &rotation; }
	inline glm::vec3* GetScale() { return &scaler; }

	///Summary<>
	//Settings for the position, rotation and scale - simply sets the positon of the model
	inline void SetPos(glm::vec3& pos) { this->position = pos; } 
	inline void SetRot(glm::vec3& rot) { this->rotation = rot; }
	inline void SetScale(glm::vec3& scale) { this->scaler = scale; }
protected:
private:
	///summary<>
	//The varaibles that are beingh used
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scaler;
};

