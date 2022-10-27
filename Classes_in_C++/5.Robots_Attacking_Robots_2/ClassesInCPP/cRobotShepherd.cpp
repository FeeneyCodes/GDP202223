#include "cRobotShepherd.h"

#include "cRobot.h"	// This is the ACTUAL robot, not interface
#include "cKaiju.h"

// HACK
cKaiju* g_Gozzila;

cRobotShepherd::cRobotShepherd()
{
	::g_Gozzila = new cKaiju();
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

iDamage* cRobotShepherd::findClosestRobot(iRobot* pMeWhosAsking)
{
	iDamage* pClosestRobot = NULL;

	if ( rand() % 3 )
	{
		// 1 in 3 chance of picking Gozilla
		pClosestRobot = ::g_Gozzila;
	}
	else
	{
		// Code to find closest robot
		// I'm lazy so I'm going to just pick a random robot
		pClosestRobot = (cRobot*)this->m_vecTheRobots[rand() % 8];
	}


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

// Return true if I actually hit something... maybe
bool cRobotShepherd::ShootTheClosestRobot(iRobot* pMeWhosAsking, float amount)
{
	// 1 in 3 chance of picking Gozilla

	if (rand() % 3)
	{
		::g_Gozzila->TakeDamage(amount);
	}
	else
	{
		// Code to find closest robot
		// I'm lazy so I'm going to just pick a random robot
		cRobot* pClosestRobot = (cRobot*)this->m_vecTheRobots[rand() % 8];

		pClosestRobot->TakeDamage(amount);
	}


	return true;
}

