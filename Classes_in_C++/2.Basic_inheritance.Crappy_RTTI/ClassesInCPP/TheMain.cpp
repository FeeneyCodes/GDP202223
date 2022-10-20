#include "cAnimal.h"
#include "cWolf.h"
#include "cRabbit.h"

#include <iostream>
#include <vector>


int main()
{
	cAnimal* pThing = new cAnimal();

	cWolf* pWolf = new cWolf();
//	pWolf->type = "Wolf";
	pWolf->animalType = cAnimal::eCreatureType::WOLF;
//	cAnimal* pWolf = new cWolf();

	cRabbit* pRabbit = new cRabbit();
//	pRabbit->type = "Rabbit";
	pRabbit->animalType = cAnimal::eCreatureType::RABBIT;

	//int x = 5;
	//float y1 = (float)x;					// C style
	//float y2 = static_cast<float>(x);	// C++

//	pWolf->MakeSound();					
//	((cWolf*)pWolf)->MakeSound();
//	pRabbit->MakeSound();



	std::vector<cAnimal*> vec_pTheAnimals;
	vec_pTheAnimals.push_back(pThing);
	vec_pTheAnimals.push_back(pWolf);
	vec_pTheAnimals.push_back(pRabbit);

	std::cout << "About to loop through the animals..." << std::endl;
	for ( unsigned int index = 0; 
		  index != vec_pTheAnimals.size(); index++ )
	{
		cAnimal* pA = vec_pTheAnimals[index];

		//if ( pA->type == "Rabit" )
		//{
		//	static_cast<cRabbit*>(pA)->MakeSound();
		//}
		//else if ( pA->type == "Wolf" )
		//{
		//	static_cast<cWolf*>(pA)->MakeSound();
		//}
		//else
		//{
		//	pA->MakeSound();
		//}

		switch ( pA->animalType )
		{
		case cAnimal::eCreatureType::WOLF:
			static_cast<cRabbit*>(pA)->MakeSound();
			break;
		case cAnimal::eCreatureType::RABBIT:
			static_cast<cWolf*>(pA)->MakeSound();
			break;
		default:
			pA->MakeSound();
			break;
		}

	}


	delete pThing;
	delete pWolf;
	delete pRabbit;

//	std::vector<cWolf*> vecWolves;
//	std::vector<cRabbit*> vecRabbits;


	return 0;
}
