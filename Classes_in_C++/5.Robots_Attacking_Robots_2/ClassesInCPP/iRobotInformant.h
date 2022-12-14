#pragma once
#include "iRobot.h"
#include "iDamage.h"

// An interface class that the robots use to 
// ask about things

class iRobotInformant
{
public:
	virtual ~iRobotInformant() {} 

		// Commands that the robots can call to ask about things, 
	//  like where my robots at? 
	// Returns NULL (or 0 or nullptr) if there isn't any
	virtual iDamage* findClosestRobot(iRobot* pMeWhosAsking) = 0;

	// Return true if I actually hit something... maybe
	virtual bool ShootTheClosestRobot(iRobot* pMeWhosAsking, float amount) = 0;


};
