#include "cRabbit.h"

#include <iostream>

cRabbit::cRabbit()
{
	std::cout << "cRabbit::cRabbit() called" << std::endl;
}

cRabbit::~cRabbit()
{
	std::cout << "cRabbit::~cRabbit() called" << std::endl;
}

void cRabbit::MakeSound(void)
{
	std::cout << "cRabbit:: quietly chews and looks scared." << std::endl;
}

void cRabbit::GetFood(void)
{
	std::cout << "cRabbit::GetFood(void)" << std::endl;
}
