#include "cRobot.h"

cRobot::cRobot()
{
	this->m_ID = cRobot::m_nextID;
	// Not increment
	cRobot::m_nextID += ID_VALUE_INCREMENT;

	// Full health
	this->health = 100.0f;
}

// Note the very strange 
//static 
unsigned int cRobot::m_nextID = cRobot::STARTING_ID;

// Or something like this:
//unsigned int cRobot::m_nextID = 5000;

void cRobot::ShootRobot(void)
{
	// Find closest robot to me
	// Shoot it!

	return;
}
