#pragma once
#include "iRobot.h"

// An interface class that the robots use to 
// ask about things

class iRobotInformant
{
public:
	virtual ~iRobotInformant() {} 

		// Commands that the robots can call to ask about things, 
	//  like where my robots at? 
	// Returns NULL (or 0 or nullptr) if there isn't any
	virtual iRobot* findClosestRobot(iRobot* pMeWhosAsking) = 0;
};
