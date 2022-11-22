#ifndef _cMeshObject_HG_
#define _cMeshObject_HG_

#include <string>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <vector>

// This represents the location and orientation, etc. of 
//	a single mesh object (a bunch of triangles with colours
//	maybe textures, etc.) like a single PLY file.

class cMeshObject
{
public:
	cMeshObject();
	std::string meshName;

	// Human friendly name for this particular instance of the mesh
	std::string friendlyName;

	glm::vec3 position;     // 0,0,0 (origin)
	glm::vec3 rotation;     // 0,0,0 ration around each Euler axis
//	float scale;
	glm::vec3 scaleXYZ;
	void SetUniformScale(float newScale)
	{
		this->scaleXYZ = glm::vec3(newScale, newScale, newScale);
	}

    bool isWireframe;		// false

	// This is the "diffuse" colour
    glm::vec4 RGBA_colour;		// RGA & Alpha, 0,0,0,1 (black, with transparency of 1.0)
	
	// When true, it will overwrite the vertex colours
	bool bUse_RGBA_colour; 

	glm::vec4 specular_colour_and_power;
			// RGB is the specular highlight colour
			// w is the power

	bool bDoNotLight;

	bool bIsVisible;

	// Later (after mid-term)
	std::string textures[8];
	float textureRatios[8];


	// Child meshes - move with the parent mesh
	std::vector< cMeshObject* > vecChildMeshes;

};

#endif // _cMeshObject_HG_
