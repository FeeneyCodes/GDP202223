#include "cMeshObject.h"

//class cMeshObject
//{
//public:
//	cMeshObject();
//	std::string meshName;
//
//	glm::vec3 position;     // 0,0,0 (origin)
//	glm::vec3 rotation;     // 0,0,0 ration around each Euler axis
//	glm::vec4 colour;		// 0,0,0,1 (black)
//	float scale;
//	bool isWireframe;

cMeshObject::cMeshObject()
{
	this->position = glm::vec3(0.0f);    
	this->rotation = glm::vec3(0.0f);
	// RGB and "alpha" (A) 0.0f = transparent
	this->colour = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->scale = 1.0f;
	this->isWireframe = false;
}
