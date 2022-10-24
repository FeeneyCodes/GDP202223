
#include "cSuperRabbit.h"
#include <iostream>

cSuperRabbit::cSuperRabbit()
{
	std::cout << "cSuperRabbit::cSuperRabbit() called" << std::endl;
}

cSuperRabbit::~cSuperRabbit()
{
	std::cout << "cSuperRabbit::~cSuperRabbit() called" << std::endl;
}

void cSuperRabbit::MakeSound(void)
{
	std::cout << "cSuperRabbit:: ROAR!!! I WANT TO EAT WOLVES!" << std::endl;
}