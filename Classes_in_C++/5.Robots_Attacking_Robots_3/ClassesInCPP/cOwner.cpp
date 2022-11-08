#include "cOwner.h"

#include <iostream>

cOwner::cOwner()
{
	this->m_pMyPet = NULL;
}

void cOwner::SetPet(cPet* pThePet)
{
	this->m_pMyPet = pThePet;
}


void cOwner::TakePetForWalk(void)
{
	if ( this->m_pMyPet )
	{
		// the if compares to NULL or zero
		this->m_pMyPet->Walk();
	}

}

void cOwner::TakeCuddles(void)
{
	std::cout 
		<< this->m_name << " says: "
		<< "Who's a good girl?? YOU ARE!!" << std::endl;
}
