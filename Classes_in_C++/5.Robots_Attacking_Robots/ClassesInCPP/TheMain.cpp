#include "cRobot.h"

#include <iostream>
#include <vector>
#include <fstream> 

int main()
{
	const unsigned int NUM_ROBOTS = 10;
	std::vector<cRobot*> vecTheRobots;

	unsigned int uniqueID = 5000;

	for ( unsigned int count = 0; count != NUM_ROBOTS; count++ )
	{
//		cRobot newRobot;
		cRobot* pNewRobot = new cRobot();
//		newRobot.ID = uniqueID;

//		uniqueID += 7;

		vecTheRobots.push_back(pNewRobot);
	}


	for ( unsigned int index = 0; index != NUM_ROBOTS; index++ )
	{
		vecTheRobots[index]->vec_pAllTheRobots = vecTheRobots;
	}


	vecTheRobots[3]->health = 50.0f;

	delete vecTheRobots[3];
	vecTheRobots[3] = NULL;

	vecTheRobots[5]->vec_pAllTheRobots[3]->health = 25.0f;


	return 0;
}
