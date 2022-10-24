//#pragma once
#ifndef _cAnimal_HG_2022_10_13_
#define _cAnimal_HG_2022_10_13_

#include <string>

class iAnimal
{
public:
	// No constructor needed because we never call "new" on this
//	iAnimal();				
	virtual ~iAnimal() {};	

	// Strip everything out of this class except 
	// the functions-methods all the animal have

	// these are "pure virtual" 
	// Note the "= 0" a the end.
	// which is really strange. 
	// There isn't any code associate with this
	virtual void MakeSound(void) = 0;
	virtual void GetFood(void) = 0 ;
	// and other things...
	// virtual void Move(float delta_x, float delta_y) = 0;
	virtual void Walk(void);
	virtual void Swim(void);
	virtual void Fly(void);

	virtual void Move(void) = 0;
	
private:
};



#endif 
