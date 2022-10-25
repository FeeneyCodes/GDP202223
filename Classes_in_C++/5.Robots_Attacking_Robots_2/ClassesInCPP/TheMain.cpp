//#include "cRobot.h"

#include <iostream>
#include <vector>
#include <fstream> 

#include "cRobotShepherd.h"

int main()
{
	const unsigned int NUM_ROBOTS = 10;

	cRobotShepherd theRobots;

	for ( unsigned int count = 0; count != NUM_ROBOTS; count++ )
	{
//		iRobot* pNewRobot = new cRobot();

		iRobot* pNewRobot = theRobots.makeRobot();
		std::cout << "Created robot with ID = " << pNewRobot->getID() << std::endl;
	}


	// Main loop
	while ( true )
	{
		double deltaTime = 0.01;		// 10 ms

		theRobots.Update(deltaTime);

	}// while ( true )

	return 0;
}
