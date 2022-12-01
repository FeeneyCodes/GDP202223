#pragma once

#include <string>

struct sVec3
{
	sVec3() : x(0.0f), y(0.0f), z(0.0f) {}
	float x, y, z;
};

class cGameObject
{
public:
	cGameObject();

	std::string name;
	sVec3 position;
	sVec3 velocity;
	float health;

	unsigned int getID(void);
private:
	unsigned int m_myID;
	static unsigned int nextID;
	static const unsigned int STARTING_ID = 50;

};


