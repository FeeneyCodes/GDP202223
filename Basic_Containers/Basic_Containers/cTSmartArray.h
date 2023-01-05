#pragma once
//#include <string>

template <class T>
class cTSmartArray
{
public:
	cTSmartArray()
	{
	}
	~cTSmartArray()
	{
	}
	

	void InsertAtEnd(T newItem)
	{
		this->m_theData[this->m_EndIndex] = newItem;
		this->m_EndIndex++;
		return;
	}

	void InsertAtIndex(int index, T newItem)
	{
		// Assumes that the index is OK aka "valid"

		// 1. make room for the new value
		for (unsigned int copyIndex = (this->m_EndIndex + 1);
			 copyIndex >= index; copyIndex--)
		{
			// Copy THIS location at th 
			this->m_theData[copyIndex + 1] = this->m_theData[copyIndex];
		}

		// 2. overwrite the value at that location
		this->m_theData[index] = newItem;

		return;
	}


	unsigned int getSize(void) 
	{
		return this->m_EndIndex;
	}

	// Operator overloading the "[]" operator
	T operator[](int index)
	{
		return this->m_theData[index];
	}

	T getValueAtIndex(int index)
	{
		return this->m_theData[index];
	}

private:

	static const unsigned int ARRAY_SIZE = 5000;
	unsigned int m_EndIndex = 0;
	T m_theData[ARRAY_SIZE];
};


