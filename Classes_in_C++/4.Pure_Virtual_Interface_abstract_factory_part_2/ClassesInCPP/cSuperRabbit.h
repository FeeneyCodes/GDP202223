#pragma once

#include "cRabbit.h"

class cSuperRabbit : public cRabbit
{
public:
	cSuperRabbit();		// Called when the object is created.
	virtual ~cSuperRabbit();		// Called when the object is destroyed.

	// from iAnimal interface
	virtual void MakeSound(void);
	virtual void GetFood(void);

};