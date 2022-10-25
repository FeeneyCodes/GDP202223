#pragma once
#include <string>
#include <vector>

struct sVec3
{
	float x, y, z;
};

class cRobot
{
public:
	cRobot();

	std::string name;
	float health;
	sVec3 location;

	std::vector<cRobot*> vec_pAllTheRobots;

	void ShootRobot(void);


	
	unsigned int getID(void)
	{
		return this->m_ID;
	}
private:
	unsigned int m_ID;
	
	// Static = There's only one for ALL instances
	// Const just means I can't change it
	static const unsigned int STARTING_ID = 5000;
	static const unsigned int ID_VALUE_INCREMENT = 5000;
	// This is JUST static, not const 
	static unsigned int m_nextID;// = 5000;
};

