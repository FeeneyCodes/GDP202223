#pragma once

#include "cAnimal.h"

class cRabbit : public cAnimal
{
public:
	cRabbit();		// Called when the object is created.
	virtual ~cRabbit();		// Called when the object is destroyed.
	void MakeSound(void);

};