//#include "iAnimal.h"
#include "cAnimalFactory.h"
//#include "cWolf.h"
//#include "cRabbit.h"
//#include "cSuperRabbit.h"

#include <iostream>
#include <vector>
#include <fstream> 

int main()
{
	// Note the type of object we are creating...
	// ...NOT the type of pointer

	std::ifstream loadFile("Animals_to_Load.txt");

	cAnimalFactory theFactory;

	std::vector<iAnimal*> vec_pTheAnimals;


	std::string typeToCreate;
	while ( loadFile >> typeToCreate )
	{ 
		std::cout << "Creating a(an)..." << typeToCreate << std::endl;

		iAnimal* pAnimal = theFactory.MakeAnmial(typeToCreate);

		// Since it returns either zero (0) or non-zero 
		// I can use this if statement
		// ! pAnimal really means if ( pAnimal != ZERO )
		if ( ! pAnimal )
		{
			std::cout << "OOOPs! Didn't create anything" << std::endl;
		}
		else
		{
			vec_pTheAnimals.push_back(pAnimal);
		}

//		if ( typeToCreate == "Rabbit" )
//		{
//			pAnimal
//		}
//		if ( typeToCreate == "Wolf" )
//		{
//
//		}
//		if ( typeToCreate == "Super_Rabbit" )
//		{
//
//		}
//	


	}


//	iAnimal* pWolf = new cWolf();
//	iAnimal* pRabbit = new cRabbit();
//	iAnimal* pBugs = new cSuperRabbit();

//	std::vector<iAnimal*> vec_pTheAnimals;
//	vec_pTheAnimals.push_back(pWolf);
//	vec_pTheAnimals.push_back(pRabbit);
//	vec_pTheAnimals.push_back(pBugs);

	std::cout << "About to loop through the animals..." << std::endl;
	for ( unsigned int index = 0; 
		  index != vec_pTheAnimals.size(); index++ )
	{
		iAnimal* pA = vec_pTheAnimals[index];

		pA->MakeSound();
	}

//	std::cout << "deleting" << std::endl;
//	delete pWolf;
//	delete pRabbit;
//	delete pBugs;

//	std::vector<cWolf*> vecWolves;
//	std::vector<cRabbit*> vecRabbits;


	return 0;
}
