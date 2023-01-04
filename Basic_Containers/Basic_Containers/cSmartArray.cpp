#include "cSmartArray.h"

cSmartArray::cSmartArray()
{
}

cSmartArray::~cSmartArray()
{
}

void cSmartArray::InsertAtEnd(std::string newItem)
{
	//	std::string m_theData[ARRAY_SIZE];

	this->m_theData[this->m_EndIndex] = newItem;

	this->m_EndIndex++;

	return;
}

unsigned int cSmartArray::getSize(void)
{
	return this->m_EndIndex;
}

// Get at index location
std::string cSmartArray::operator[](int index)
{
	return this->m_theData[index];
}

std::string cSmartArray::getValueAtIndex(int index)
{
	return this->m_theData[index];
}

void cSmartArray::InsertAtIndex(int index, std::string newItem)
{
	// Assumes that the index is OK aka "valid"

	// 1. make room for the new value
	for ( unsigned int copyIndex = (this->m_EndIndex + 1);
		  copyIndex >= index; copyIndex--)
	{
		// Copy THIS location at th 
		this->m_theData[copyIndex + 1] = this->m_theData[copyIndex];
	}

	// 2. overwrite the value at that location
	this->m_theData[index] = newItem;

	return;
}
