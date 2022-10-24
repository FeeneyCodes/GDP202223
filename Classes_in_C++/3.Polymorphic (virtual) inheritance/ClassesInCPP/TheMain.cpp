#include "cAnimal.h"
#include "cWolf.h"
#include "cRabbit.h"
#include "cSuperRabbit.h"

#include <iostream>
#include <vector>


int main()
{
	cAnimal* pThing = new cAnimal();

	// Note the type of object we are creating...
	// ...NOT the type of pointer
	cAnimal* pWolf = new cWolf();

	cAnimal* pRabbit = new cRabbit();

	cAnimal* pBugs = new cSuperRabbit();

	// Also create a fish...


	std::vector<cAnimal*> vec_pTheAnimals;
	vec_pTheAnimals.push_back(pThing);
	vec_pTheAnimals.push_back(pWolf);
	vec_pTheAnimals.push_back(pRabbit);
	vec_pTheAnimals.push_back(pBugs);

	std::cout << "About to loop through the animals..." << std::endl;
	for ( unsigned int index = 0; 
		  index != vec_pTheAnimals.size(); index++ )
	{
		cAnimal* pA = vec_pTheAnimals[index];

		pA->MakeSound();
	}

	std::cout << "deleting" << std::endl;
	delete pThing;
	delete pWolf;
	delete pRabbit;
	delete pBugs;

//	std::vector<cWolf*> vecWolves;
//	std::vector<cRabbit*> vecRabbits;


	return 0;
}
