#pragma once

// This is a pet Owner

#include <string>
#include "cPet.h"

class cOwner
{
public:
	cOwner();
//	cOwner(cPet* pThePet);
	// Called to set the pointer to the pet instance
	void SetPet(cPet* pThePet);

	void TakeCuddles(void);

	int height;
	std::string m_name;

	void TakePetForWalk(void);

private:
	cPet* m_pMyPet;

};
