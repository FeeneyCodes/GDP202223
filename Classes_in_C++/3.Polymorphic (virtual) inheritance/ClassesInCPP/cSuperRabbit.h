#pragma once

#include "cRabbit.h"

class cSuperRabbit : public cRabbit
{
public:
	cSuperRabbit();		// Called when the object is created.
	virtual ~cSuperRabbit();		// Called when the object is destroyed.
	void MakeSound(void);

};