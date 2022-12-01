#pragma once

#include <string>

struct sVec3
{
	float x, y, z;
};

class cGameObject
{
public:
	cGameObject();

	std::string name;
	sVec3 position;

	unsigned int getID(void);
private:
	unsigned int m_myID;
	static unsigned int nextID;
	static const unsigned int STARTING_ID = 50;

};


