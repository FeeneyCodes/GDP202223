#include <vector>
#include <iostream>
#include <string>
#include "cMeshObject.h"

void vectorStuffFunction(void)
{
	// array
	int myArray[10];	// 10 integers
	myArray[0] = 3;
	myArray[5] = 13;
//	myArray[999] = 23;		// YIKES!!!

	std::cout << myArray[5];

	int myArray1[10];

	std::vector<int> myVector;

	// Allows for familiar "array" type syntax.
	// i.e. it's writen to pretend to be like an array.
//	myVector[0] = 3;		// YIKES!!!
//	myVector[5] = 13;
//	myVector[999] = 23;		
//
//	std::cout << myVector[5];

	// "Pushed" or "added" something on the "back" of the vector
	// Or it's been added to the "end" of the vector
	myVector.push_back(3);	// 1st item, so at index 0, so now: myVector[0] = 3
	myVector.push_back(5423);	// 1st item, so at index 0, so now: myVector[0] = 3
	myVector.push_back(-234);	// 1st item, so at index 0, so now: myVector[0] = 3

	std::cout << myVector[0];		// 3
	std::cout << myVector[1];		// 5423
	std::cout << myVector[2];		// -234

	for ( unsigned int index = 0; index != 3; index++ )
	{
		std::cout << myVector[index] << std::endl;
	}

	for ( unsigned int index = 0; index != myVector.size(); index++ )
	{
		std::cout << myVector[index] << std::endl;
	}


	std::vector<std::string> myVectorOfStrings;
	std::vector<double> myVectorOfDoubles;

	std::vector< std::vector<int> > myVectorOfVectorsOfInts;	//AKA a 2D array

	std::vector<cMeshObject> vecOfMeshObjects;

	cMeshObject myArrayOfMeshes[10];


	cMeshObject* myArrayOfMeshesPointers[10];
	std::vector< cMeshObject* > vecOfPointersToMeshObjects;

	return;
}