#include "cAnimalFactory.h"
// 
#include "cRabbit.h"
#include "cWolf.h"
#include "cSuperRabbit.h"


iAnimal* cAnimalFactory::MakeAnmial(std::string typeToMake)
{
	iAnimal* pTheAnimal = NULL;

	// AMAZING CODE HERE
	if ( typeToMake == "Rabbit" )
	{
		pTheAnimal = new cRabbit();
	}
	if ( typeToMake == "Wolf" )
	{
		pTheAnimal = new cWolf();
	}
	if ( typeToMake == "Super_Rabbit" )
	{
		pTheAnimal = new cSuperRabbit();
	}

	return pTheAnimal;
}



cAnimalFactory::cAnimalFactory()
{

}

cAnimalFactory::~cAnimalFactory()
{

}