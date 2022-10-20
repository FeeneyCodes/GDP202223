#include "cAnimal.h"
#include <iostream>
#include <vector>


int main2()
{
	std::cout << "Hey" << std::endl;

	cAnimal* pADog = new cAnimal();

	// This is C++14 I think...
//	cAnimal* pADog2 = new cAnimal{"Mike", "Dog"};


	cAnimal aDawg;
	aDawg.name = "Rex";

	std::vector<cAnimal> vecAnimals;

	// "Copy in, Copy out"
	vecAnimals.push_back(aDawg);

	aDawg.name = "Sally";

	std::cout << aDawg.name << std::endl;
	std::cout << vecAnimals[0].name << std::endl;

	std::cout << "there" << std::endl;

//	cAnimal* pDawg = new cAnimal();

//	delete pDawg;

	return 0;
}

int main3()
{
	std::cout << "Hey" << std::endl;

	cAnimal* aDawg = new cAnimal();;
	aDawg->name = "Rex";

	std::vector< cAnimal* > vecAnimals;

	// "Copy in, Copy out"
	vecAnimals.push_back(aDawg);

	aDawg->name = "Sally";

	std::cout << aDawg->name << std::endl;
	std::cout << vecAnimals[0]->name << std::endl;

	std::cout << "there" << std::endl;

//	cAnimal* pDawg = new cAnimal();

//	delete pDawg;

	return 0;
}
