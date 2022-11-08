#include "cKaiju.h"
#include <iostream>

cKaiju::cKaiju()
{
	this->health = 1000.0f;
}


void cKaiju::TakeDamage(float amount)
{
	std::cout << "cKaiju takes " << amount << " damage!!" << std::endl;
	return;
}