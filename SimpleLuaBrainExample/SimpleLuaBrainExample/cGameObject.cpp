#include "cGameObject.h"

cGameObject::cGameObject()
{
	this->m_myID = cGameObject::nextID;
	cGameObject::nextID += 1;
	// 
	this->health = 100.0f;
}

//static 
unsigned int cGameObject::nextID = cGameObject::STARTING_ID;

unsigned int cGameObject::getID(void)
{
	return this->m_myID;
}
