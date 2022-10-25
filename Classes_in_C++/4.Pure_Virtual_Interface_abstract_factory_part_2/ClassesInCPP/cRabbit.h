#pragma once

#include "iAnimal.h"
#include "sAnimalData.h"

class cRabbit : public iAnimal
{
public:
	cRabbit();		// Called when the object is created.
	virtual ~cRabbit();		// Called when the object is destroyed.

	// from iAnimal interface
	virtual void MakeSound(void);
	virtual void GetFood(void);
	virtual void Move(void);

	sAnimalData theData;

private:
	int shoeSize;

};