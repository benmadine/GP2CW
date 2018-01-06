#pragma once
//Includes
#include <glm\glm.hpp>
#include <GL\glew.h>
#include <string>
#include "obj_loader.h"


struct VertextManager //Vertex manager data structure
{
public:

	VertextManager(const glm::vec3 & position, const glm::vec2& texCord, const glm::vec3& norms) //Vertex Manager method takes in three arguments
	{
		this->position = position; //Position
		this->texPos = texCord; // textutre position
		this->norms = norms; //the normals
	}

	///Summmary <>
	//The getters fro the variables
	glm::vec3* GetPosition() { return &position; }
	glm::vec2* GetTexCoordinate() { return &texPos; }
	glm::vec3* GetNormal() { return &norms; }

	//The variables
	glm::vec3 position; //Vector 3 position
	glm::vec2 texPos; //vector 2 texture position
	glm::vec3 norms; //Vector 3 normals

protected:
private:

};

struct  SphereCollider //Sphere Collider data structure, used when doing collisions
{
public:
	SphereCollider() {} //Constructor

	SphereCollider(glm::vec3& position, float circleRadius) //Sphere collider method, two arguments: the position of the sphere and the radius of the sphere
	{
		this->position = position; //The position varaible
	}

	///Summary <>
	//The getters, one for the radius and one for the circle radius
	glm::vec3 GetPosition() { return position; }
	float GetCircleRadius() { return circleRadius; }

	void SetPosition(glm::vec3 position) //Setting the position of the circle collider
	{
		this->position = position;
	}

	void SetCircleRadius(float circleRadius) //Set the circle radius
	{
		this->circleRadius = circleRadius;
	}

	glm::vec3 position; //Position vector 3 varaible
	float circleRadius; //circle radius float 
};


class MeshManager
{
public:
	MeshManager();
	~MeshManager();



	void Drawing();
	void initailise(VertextManager* verts, unsigned int numberVerts, unsigned int* indices, unsigned int indicesNumber);
	void modelLoader(const std::string& fileTitle);
	void initaliseModel(const IndexedModel& theModel);

	void sphereDataUpdate(glm::vec3 position, float circleRadius);

	glm::vec3 getSpherePosition() 
	{
		return sphereMesh.GetPosition();
	}

	float getSphereRadui()

	{
		return sphereMesh.GetCircleRadius();
	}

private:
	enum MyEnum
	{
		POSITION_VERTXBUFF, TEXCOORD_VB, NORMAL_VB, INDEX_VB, NUM_BUFF
	};

	GLuint vertArrayObj;
	GLuint vertArryBuff[NUM_BUFF];
	unsigned int drawCounter;
	SphereCollider sphereMesh;
};


