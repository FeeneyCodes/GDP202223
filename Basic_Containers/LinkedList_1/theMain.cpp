#include <fstream>
#include <string>
#include <iostream>
#include "cLinkedList_1.h"

int main()
{
	std::ifstream nameFile("dist.female.first.txt");
//	std::ifstream nameFile("US_LastNames.txt");

	// Read each name and save in a smart array
	std::string tempName;

	cLinkedList_1 llNames;

	// MARY    2.629    2.629     1
	while (nameFile >> tempName)
	{
		float discard = 0.0f;

		nameFile >> discard >> discard >> discard;

//		std::cout << tempName << std::endl;
		// Add to smart array
		llNames.insert(tempName);
	}

	// 997 HERMINIA       0.008 81.836    998
	// 998 TERRA          0.008 81.844    999
	// 999 CELINA         0.008 81.852   1000
	// 1000	TORI           0.008 81.861   1001
	// 1001 OCTAVIA        0.008 81.869   1002
//
//	saNames.InsertAtIndex(999, "Lord Voldemort!");

	llNames.moveToHead();
	do
	{
		std::cout << llNames.getValue() << std::endl;

		llNames.moveNext();

	} while ( ! llNames.isAtTail() );

//	for (unsigned int index = 0; index != saNames.getSize(); index++)
//	{
//		std::cout
//			<< index << " : ";
//			<< saNames.getValueAtIndex(index) << std::endl;
//	}


	return 0;
}