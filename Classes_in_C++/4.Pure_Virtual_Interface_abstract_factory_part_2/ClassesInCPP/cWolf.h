#pragma once

#include "iAnimal.h"
#include "sAnimalData.h"


class cWolf : public iAnimal
{
public:
	cWolf();		// Called when the object is created.
	virtual ~cWolf();		// Called when the object is destroyed.

	// from iAnimal interface
	virtual void MakeSound(void);
	virtual void GetFood(void);

	sAnimalData theData;

//	iMovementThing* pMover;
//	iBrain* pBehavior;
};