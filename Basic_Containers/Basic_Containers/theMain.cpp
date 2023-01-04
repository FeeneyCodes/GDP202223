#include <fstream>
#include <string>
#include <iostream>

#include "cSmartArray.h"

void AAAAAH(void);

int main()
{

//	AAAAAH();

	std::ifstream nameFile("dist.female.first.txt");

	// Read each name and save in a smart array
	std::string tempName;

	cSmartArray saNames;

	// MARY    2.629    2.629     1
	while ( nameFile >> tempName )
	{
		float discard = 0.0f;

		nameFile >> discard >> discard >> discard;

//		std::cout << tempName << std::endl;
		// Add to smart array
		saNames.InsertAtEnd(tempName);
	}

	// 997 HERMINIA       0.008 81.836    998
	// 998 TERRA          0.008 81.844    999
	// 999 CELINA         0.008 81.852   1000
	// 1000	TORI           0.008 81.861   1001
	// 1001 OCTAVIA        0.008 81.869   1002

	saNames.InsertAtIndex(999, "Lord Voldemort!");

//	for ( unsigned int index = 0; index != saNames.getSize(); index++ )
	for ( unsigned int index = 990; index != 1010; index++ )
	{
		std::cout
			<< index << " : "
			<< saNames.getValueAtIndex(index) << std::endl;
	//		<< saNames[index] << std::endl;
	//		<< saNames.operator[](index) << std::endl;
	}


	return 0;
}

#include <vector>
void AAAAAH(void)
{
	std::vector<std::string> myVector;
	myVector.push_back("Michael");
	myVector.push_back("Robin");

//	myVector.insert(myVector.begin()+1, "Fraser");

	std::vector<std::string>::iterator itWhereToInsert
		= myVector.begin();

	itWhereToInsert++;

	myVector.insert(itWhereToInsert, "Fraser");

	return;

}