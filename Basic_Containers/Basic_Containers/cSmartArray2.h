#pragma once

#pragma once

#include <string>

class cSmartArray2
{
public:
	cSmartArray2();
	~cSmartArray2();

	void InsertAtEnd(std::string newItem);		// push_back
	void InsertAtIndex(int index, std::string newItem);

	unsigned int getSize(void);

	// Operator overloading the "[]" operator
	std::string operator[](int index);
	std::string getValueAtIndex(int index);

private:

//	static const unsigned int ARRAY_SIZE = 5000;
	unsigned int m_EndIndex = 0;
//	std::string m_theData[ARRAY_SIZE];

	// Point to what? An array
	unsigned int m_currentSizeOfArray;
	std::string* m_theData;

	void m_AllocateSpace(void);
};


