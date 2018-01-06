                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          #include "MeshManager.h"
#include <vector>

void MeshManager::initailise(VertextManager* verts, unsigned int numberVerts, unsigned int* indices, unsigned int indicesNumber) //Initailise method 
{
	IndexedModel theModel;

	for (unsigned int i = 0; i < numberVerts; i++) //Forloop for the number of vertices in the mesh
	{
#pragma region Adding elements to certain arrays
		//Pushes the elements into certain arrats
		theModel.positions.push_back(*verts[i].GetPosition());
		theModel.texCoords.push_back(*verts[i].GetTexCoordinate());
		theModel.normals.push_back(*verts[i].GetNormal());
#pragma endregion
	}

	for (unsigned int i = 0; i < indicesNumber; i++) //For loop for the indices
		theModel.indices.push_back(indices[i]); //Adding the indices to the indices array

	initaliseModel(theModel); //Initalise the model
}

void MeshManager::initaliseModel(const IndexedModel& theModel) //Initalised model method
{
	drawCounter = theModel.indices.size(); //draw counter is set to the size of indices

	///Summary<Buffers>
	//Each buffer is adding elements to the array, then, assinging them to the correct buffer
	//Once this is done then they are sent to the graphics card
	///Summary<Buffers>

#pragma region Buffers

	glGenVertexArrays(1, &vertArrayObj);
	glBindVertexArray(vertArrayObj);

	glGenBuffers(NUM_BUFF, vertArryBuff);

	glBindBuffer(GL_ARRAY_BUFFER, vertArryBuff[POSITION_VERTXBUFF]);
	glBufferData(GL_ARRAY_BUFFER, theModel.positions.size() * sizeof(theModel.positions[0]), &theModel.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArryBuff[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, theModel.positions.size() * sizeof(theModel.texCoords[0]), &theModel.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertArryBuff[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(theModel.normals[0]) * theModel.normals.size(), &theModel.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertArryBuff[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, theModel.indices.size() * sizeof(theModel.indices[0]), &theModel.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
#pragma endregion

}


MeshManager::MeshManager()
{
	drawCounter = NULL;
}

void MeshManager::modelLoader(const std::string& fileTitle) //Loads the model
{
	IndexedModel theModel = OBJModel(fileTitle).ToIndexedModel();
	initaliseModel(theModel);
	SphereCollider sphereMesh();
}

MeshManager::~MeshManager()
{
	//This deletes the vertext arrays
	glDeleteVertexArrays(1, &vertArrayObj);
}

void MeshManager::Drawing()
{
	///<summary>
	///This code binds the VAO and draws the triangles.
	///<summary>
	glBindVertexArray(vertArrayObj);
	glDrawElements(GL_TRIANGLES, drawCounter, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void MeshManager::sphereDataUpdate(glm::vec3 position, float circleRadius) //Updates the sphere collider
{
	sphereMesh.SetPosition(position); //Sphere collder position
	sphereMesh.SetCircleRadius(circleRadius); //Sphere collider radius
}
