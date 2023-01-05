#include "cSmartArray2.h"

cSmartArray2::cSmartArray2()
{
	// Allocate the array
//	unsigned int m_currentSizeOfArray;
//	std::string* m_theData;

//	this->m_currentSizeOfArray = 5000;
//	this->m_theData = new std::string[this->m_currentSizeOfArray];

	this->m_currentSizeOfArray = 5000;

	this->m_AllocateSpace();

}

cSmartArray2::~cSmartArray2()
{
	delete [] this->m_theData;
}

void cSmartArray2::m_AllocateSpace(void)
{
	// Allocate memory for this array
	this->m_theData = new std::string[this->m_currentSizeOfArray];
}


void cSmartArray2::InsertAtEnd(std::string newItem)
{
	//	std::string m_theData[ARRAY_SIZE];

	// Are we at the end of the ACTUAL array
	if ( this->m_EndIndex >= this->m_currentSizeOfArray )
	{
		// OOOOPS! We don't have space

		// TODO: Make space
		// 1. Make a bigger array
		unsigned int newSize = this->m_currentSizeOfArray * 2;
		std::string* newArray = new std::string[newSize];

		// 2. Copy everything into that bigger array
		for (unsigned int index = 0; index != this->m_EndIndex; index++ )
		{
			newArray[index] = this->m_theData[index];
		}

		// 3. Delete the old one
		delete[] this->m_theData;

		// Point the pointer to the new array
		this->m_theData = newArray;
		this->m_currentSizeOfArray = newSize;
	}

	// At this point, assume there is enough space 
	this->m_theData[this->m_EndIndex] = newItem;

	this->m_EndIndex++;

	return;
}

unsigned int cSmartArray2::getSize(void)
{
	return this->m_EndIndex;
}

// Get at index location
std::string cSmartArray2::operator[](int index)
{
	return this->m_theData[index];
}

std::string cSmartArray2::getValueAtIndex(int index)
{
	return this->m_theData[index];
}

void cSmartArray2::InsertAtIndex(int index, std::string newItem)
{
	// Assumes that the index is OK aka "valid"

	// 1. make room for the new value
	for (int copyIndex = (this->m_EndIndex + 1);
		 copyIndex >= index; copyIndex--)
	{
		// Copy THIS location at th 
		this->m_theData[copyIndex + 1] = this->m_theData[copyIndex];
	}

	// 2. overwrite the value at that location
	this->m_theData[index] = newItem;

	return;
}
