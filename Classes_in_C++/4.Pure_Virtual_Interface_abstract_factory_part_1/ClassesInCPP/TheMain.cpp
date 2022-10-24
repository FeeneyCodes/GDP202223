#include "iAnimal.h"
#include "cWolf.h"
#include "cRabbit.h"
#include "cSuperRabbit.h"

#include <iostream>
#include <vector>
#include <fstream> 

int main()
{
	// Note the type of object we are creating...
	// ...NOT the type of pointer
	iAnimal* pWolf = new cWolf();

	iAnimal* pRabbit = new cRabbit();

	iAnimal* pBugs = new cSuperRabbit();

	// Also create a fish...


	std::vector<iAnimal*> vec_pTheAnimals;
	vec_pTheAnimals.push_back(pWolf);
	vec_pTheAnimals.push_back(pRabbit);
	vec_pTheAnimals.push_back(pBugs);

	std::cout << "About to loop through the animals..." << std::endl;
	for ( unsigned int index = 0; 
		  index != vec_pTheAnimals.size(); index++ )
	{
		iAnimal* pA = vec_pTheAnimals[index];

		pA->MakeSound();
	}

	std::cout << "deleting" << std::endl;
	delete pWolf;
	delete pRabbit;
	delete pBugs;

//	std::vector<cWolf*> vecWolves;
//	std::vector<cRabbit*> vecRabbits;


	return 0;
}
