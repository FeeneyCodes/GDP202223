#include "cLuaBrain/cLuaBrain.h"
#include "cGameObject.h"
#include <vector>
#include <iostream>

int main()
{


	std::vector< cGameObject* > vec_pGOs;

	cGameObject* p_Bob = new cGameObject();
	cGameObject* p_Sally = new cGameObject();
	cGameObject* p_Ali = new cGameObject();

	p_Bob->name = "Bob";
	p_Sally->name = "Sally";
	p_Ali->name = "Ali";

	vec_pGOs.push_back(p_Bob);
	vec_pGOs.push_back(p_Sally);
	vec_pGOs.push_back(p_Ali);

	cLuaBrain* pBrain = new cLuaBrain();

	// Pass the address of (aka "a pointer to") 
	//	the vector of game object pointers
	// (i.e. it's NOT a copy of the vector)
	pBrain->SetObjectVector( &vec_pGOs );




	delete pBrain;

	return 0;
}
