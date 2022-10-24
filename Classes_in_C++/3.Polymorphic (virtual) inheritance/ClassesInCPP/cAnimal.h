//#pragma once
#ifndef _cAnimal_HG_2022_10_13_
#define _cAnimal_HG_2022_10_13_

#include <string>

class cAnimal
{
public:
	cAnimal();		// Called when the object is created.
	// This is NOT vitual, so is BAD, BAD, BAD
	virtual ~cAnimal();		// Called when the object is destroyed.
	std::string name;
	//std::string type;
//	enum eCreatureType
//	{
//		UNKOWN,
//		WOLF,
//		RABBIT,
//		T_REX
//	};
//	eCreatureType animalType;
	std::string soundIMake;
	float health;		// 0 to 100
	float weight;
	float height;
	unsigned int numberOfLegs;

	// This is the "polymorphic" function
	virtual void MakeSound(void);

	// WARNING: this method is NOT polymorphic
	void GetFood(void);
	
	// This clears the class to a default state
	void Initialize(void);
private:
	int shoeSize;
};


//	cAnimal(const cAnimal& t);	// "copy" constructor
	// Non-Default constructors
//	cAnimal(std::string theName, std::string theType);


#endif 
