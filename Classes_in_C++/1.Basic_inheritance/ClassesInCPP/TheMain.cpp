#include "cAnimal.h"
#include "cWolf.h"
#include "cRabbit.h"

#include <iostream>
#include <vector>


int main()
{
	cAnimal* pThing = new cAnimal();

	cWolf* pWolf = new cWolf();
//	cAnimal* pWolf = new cWolf();

	cRabbit* pRabbit = new cRabbit();

	//int x = 5;
	//float y1 = (float)x;					// C style
	//float y2 = static_cast<float>(x);	// C++

	pWolf->MakeSound();					
	((cWolf*)pWolf)->MakeSound();
	pRabbit->MakeSound();



	std::vector<cAnimal*> vec_pTheAnimals;
	vec_pTheAnimals.push_back(pThing);
	vec_pTheAnimals.push_back(pWolf);
	vec_pTheAnimals.push_back(pRabbit);

	std::cout << "About to loop through the animals..." << std::endl;
	for ( unsigned int index = 0; 
		  index != vec_pTheAnimals.size(); index++ )
	{
		vec_pTheAnimals[index]->MakeSound();
	}


	delete pThing;
	delete pWolf;
	delete pRabbit;

//	std::vector<cWolf*> vecWolves;
//	std::vector<cRabbit*> vecRabbits;


	return 0;
}
