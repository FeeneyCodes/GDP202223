#include "cWolf.h"

#include <iostream>

cWolf::cWolf()
{
	std::cout << "cWolf::cWolf() called" << std::endl;
}

cWolf::~cWolf()
{
	std::cout << "cWolf::~cWolf() called" << std::endl;
}

void cWolf::MakeSound(void)
{
	std::cout << "cWolf:: Hooowl!!!" << std::endl;
}
