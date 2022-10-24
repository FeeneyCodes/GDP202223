#pragma once

// ONLY include the INTERFACE class.
// 
// ***NEVER*** the actual specific classes 

#include "iAnimal.h"

class cAnimalFactory
{
public:
	cAnimalFactory();
	~cAnimalFactory();

	// The "creation" type needs to be a general 
	//	type that everything knows about, like int or string
	//  but DON'T make it an enum.

	// Note that I'm returning a pointer to the type
	// 
	// Will return zero or NULL or nulptr if it 
	//	doesn't understand
	iAnimal* MakeAnmial(std::string typeToMake);

	// You could also make this a stack based varible
	// by doing something like this... 
	// (The issue is what happens when you ask for 
	//	a type it doesn't understand)
//	bool MakeAnimal(std::string typeToMake,
//					iAnimal& theAnimal);
};

