#include "cPet.h"

#include "cOwner.h"

cPet::cPet()
{
	this->m_pMyOwner = nullptr;
}

void cPet::Walk(void)
{
	this->CuddleOwner();

}

void cPet::SetOwner(cOwner* pMyOwner)
{
	this->m_pMyOwner = pMyOwner;
}


void cPet::CuddleOwner(void)
{
	this->m_pMyOwner->TakeCuddles();

}
