#pragma once

#include <string>

class cSmartArray
{
public:
	cSmartArray();
	~cSmartArray();

	void InsertAtEnd(std::string newItem);		// push_back
	void InsertAtIndex(int index, std::string newItem);


	unsigned int getSize(void);

	// Operator overloading the "[]" operator
	std::string operator[](int index);
	std::string getValueAtIndex(int index);

private:

	static const unsigned int ARRAY_SIZE = 5000;
	unsigned int m_EndIndex = 0;
	std::string m_theData[ARRAY_SIZE];
};


