#ifndef _globalThings_HG_
#define _globalThings_HG_

// This is anything that is shared by all (or many) of the files

#include "cMeshObject.h"

#include "cLightManager.h"

#include <vector>

// extern means the variable isn't actually here...
// ...it's somewhere else (in a .cpp file somewhere)
extern cLightManager* g_pTheLightManager;

extern std::vector< cMeshObject* > vec_pMeshObjects;

// Returns NULL if it didn't find anything
cMeshObject* findObjectByFriendlyName(std::string name, 
									  std::vector< cMeshObject* > vec_pMeshObjects,
									  bool bSearchChildren = true);

float getRandomFloatInRange(float a, float b);

#endif
