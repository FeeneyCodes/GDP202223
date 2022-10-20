#include "cAnimal.h"
#include <iostream>

// Default constructor
cAnimal::cAnimal()		
{
	std::cout << "cAnimal::cAnimal() called" << std::endl;

	//this->health = 100.0f;		// 0 to 100
	//this->weight = -1.0f;		// Maybe -1 is invalid
	//this->height = 0.0f;
	//unsigned int numberOfLegs;

	this->Initialize();
}

//cAnimal::cAnimal() : // Initializer list
//	health(100.0f), 
//	weight(-1.0f), 
//	height(0.0f)
//{
//	std::cout << "cAnimal::cAnimal() called" << std::endl;
//
//	unsigned int numberOfLegs;
//}

//cAnimal::cAnimal(const cAnimal& t)
//{
//	std::cout << "cAnimal::cAnimal(cAnimal& t) called" << std::endl;
//
//	this->Initialize();
//
//	this->name = t.name;
//	// And the rest of the items
//}

//cAnimal::cAnimal(std::string theName, std::string theType)
//{
//	this->Initialize();
//	// 
//	this->name = theName;
//	this->type = theType;
//}

// All the constructors call this
void cAnimal::Initialize(void)
{
	this->health = 100.0f;		// 0 to 100
	this->weight = -1.0f;		// Maybe -1 is invalid
	this->height = 0.0f;
	this->numberOfLegs = 0;
}



cAnimal::~cAnimal()
{
	std::cout << "cAnimal::~cAnimal() called" << std::endl;
}

void cAnimal::MakeSound(void)
{
	std::cout << "cAnimal::<UNKNONW SOUND>" << std::endl;
}
