#include "cRobotShepherd.h"

#include "cRobot.h"	// This is the ACTUAL robot, not interface

cRobotShepherd::cRobotShepherd()
{
}

iRobot* cRobotShepherd::makeRobot(void)
{

	iRobot* pNewRobot = new cRobot();

	// Tell the robot about the shepherd
	static_cast<cRobot*>(pNewRobot)->SetRobotShepherd(this);

	// Add the robot to the list of robots
	this->m_vecTheRobots.push_back(pNewRobot);

	return pNewRobot;
}

iRobot* cRobotShepherd::findClosestRobot(iRobot* pMeWhosAsking)
{
	iRobot* pClosestRobot = NULL;

	// Code to find closest robot


	return pClosestRobot;
}

void cRobotShepherd::Update(double deltaTime)
{
	for ( unsigned int index = 0; index != this->m_vecTheRobots.size();
		  index++ )
	{
		this->m_vecTheRobots[index]->Update(deltaTime);
	}

	return;
}
