#pragma once

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

class cMeshObject
{
public:
	std::string meshName;

	glm::vec3 position;
	glm::vec3 rotation;
	float scale;

	std::string textures[10];

};
