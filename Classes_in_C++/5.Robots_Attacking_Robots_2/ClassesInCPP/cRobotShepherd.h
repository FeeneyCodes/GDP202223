#pragma once

#include "iRobot.h"
#include "iRobotInformant.h"
#include <vector>

// This is:
// * the factory object to create robots
// * keeps track of robots for other robots
class cRobotShepherd : 
	public iRobotInformant			// Interface
{
public:
	cRobotShepherd();

	// Factory method
	iRobot* makeRobot(void);
	//iRobot* makeRobot(std::string robotType);

	// Commands that the robots can call to ask about things, 
	//  like where my robots at? 
	// Returns NULL (or 0 or nullptr) if there isn't any
	iRobot* findClosestRobot(iRobot* pMeWhosAsking);

	iRobot* askSomething(std::string thingIWantToAsk);

	// or you could do this, where returning false means there isn't one
//	bool findClosestRobot(iRobot* pMeWhosAsking, iRobot* &pClosestRobot);

	// Calls update on all the robots
	void Update(double deltaTime);

private:
	std::vector<iRobot*> m_vecTheRobots;

};
