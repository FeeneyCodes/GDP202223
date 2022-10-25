//#pragma once
#ifndef _iRobot_HG_2022_10_13_
#define _iRobot_HG_2022_10_13_

#include <string>

class iRobot
{
public:
	// No constructor needed because we never call "new" on this
//	iAnimal();				
	virtual ~iRobot() {};

	virtual unsigned int getID(void) = 0;

};



#endif 
