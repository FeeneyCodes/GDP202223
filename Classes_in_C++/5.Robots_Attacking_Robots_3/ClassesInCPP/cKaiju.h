#pragma once

#include "iDamage.h"

class cKaiju : 
	public iDamage
{
public:
	cKaiju();
	// Methods completely different from the robot...


	// from the iDamage interface
	virtual void TakeDamage(float amount);

	float health;

};

