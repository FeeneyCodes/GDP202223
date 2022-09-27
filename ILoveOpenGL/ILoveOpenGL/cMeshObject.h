#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

// This represents the location and orientation, etc. of 
//	a single mesh object (a bunch of triangles with colours
//	maybe textures, etc.) like a single PLY file.

class cMeshObject
{
public:
	cMeshObject();
	std::string meshName;

	glm::vec3 position;     // 0,0,0 (origin)
	glm::vec3 rotation;     // 0,0,0 ration around each Euler axis
    glm::vec4 colour;		// 0,0,0,1 (black)
	float scale;
    bool isWireframe;		// false

	std::string textures[10];

};

#endif // _cMeshObject_HG_
