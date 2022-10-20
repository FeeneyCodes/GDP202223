#pragma once

#include "cAnimal.h"

class cWolf : public cAnimal
{
public:
	cWolf();		// Called when the object is created.
	~cWolf();		// Called when the object is destroyed.
	void MakeSound(void);
};