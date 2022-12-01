#include "cLuaBrain/cLuaBrain.h"
#include "cGameObject.h"
#include <vector>
#include <iostream>
#include <sstream>

void DoThis()
{

	return;
}

// From here: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624

float getRandomFloatInRange(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

int main()
{
//	std::cout << "The DoThis() function is at memory location: ";
//	void* pDoThis = DoThis;
//	void* pDoThis = cLuaBrain::Lua_GetObjectState;
//	std::cout << pDoThis << std::endl;

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


	// Call run script immediately to show how this might work
//	std::string myScriptText = "print(34 + 18)";
//	pBrain->RunScriptImmediately(myScriptText);

	std::stringstream ssUpdateBob;
	ssUpdateBob
		<< "setObjectState( "
		<< p_Bob->getID() << ", "
		<< " 15, 10, 5, "		// Position
		<< " -1, 0, 0 "			// Velocity
		<< ")";

	std::string myScriptText = ssUpdateBob.str();
	pBrain->RunScriptImmediately(myScriptText);

//	pBrain->RunScriptImmediately("updateObjectName()");

//	pBrain->RunScriptImmediately("updateObjectName( 50, 'Frank' )");


	pBrain->RunScriptImmediately("getObjectState( 50 )");

	pBrain->RunScriptImmediately("print( getObjectState( -5 ) )");


	// Move Bob's game object over time

	ssUpdateBob.str() = "";	// Clear the string stream (yes, it's a stupid looking call)
	ssUpdateBob
		<< "setObjectState( "
		<< p_Bob->getID() << ", "
		<< " 0, 0, 0, "		// Position
		<< " 0.1, 0, 0 "		// Velocity
		<< ")";

	myScriptText = ssUpdateBob.str();
	pBrain->RunScriptImmediately(myScriptText);

	pBrain->RunScriptImmediately(" currentTime = 0.0 ");
	pBrain->RunScriptImmediately(" deltaTime = 0.0 ");

//	std::string moveScript =
//		"isValid, x, y, z, vx, vy, vz = getObjectState(50) \n"  \
//		"if isValid then \n"									\
//		"	x = x + vx	\n"										\
//		"	y = y + vy	\n"										\
//		"	z = z + vz	\n"										\
//		"	setObjectState( 50, x, y, z, vx, vy, vz )	\n"		\
//		"end";
//	pBrain->LoadScript("Move", moveScript);

//	std::string moveScriptDeltaTime =
//		"isValid, x, y, z, vx, vy, vz = getObjectState(50) \n"  \
//		"if isValid then \n"									\
//		"	x = x + (vx * deltaTime)	\n"										\
//		"	y = y + (vy	* deltaTime)	\n"										\
//		"	z = z + (vz * deltaTime)	\n"										\
//		"	setObjectState( 50, x, y, z, vx, vy, vz )	\n"		\
//		"end";
//	pBrain->LoadScript("Move", moveScriptDeltaTime);


	// You could also save this update as a Lua script, then call it later
	std::string moveScriptDeltaTimeFUNCTION =
		"function moveObject( objectID )\n"							\
		"	isValid, x, y, z, vx, vy, vz = getObjectState(objectID) \n"	\
		"	if isValid then \n"										\
		"		x = x + (vx * deltaTime)	\n"						\
		"		y = y + (vy	* deltaTime)	\n"						\
		"		z = z + (vz * deltaTime)	\n"						\
		"		setObjectState( 50, x, y, z, vx, vy, vz )	\n"		\
		"	end	\n"													\
		"end";
	pBrain->RunScriptImmediately(moveScriptDeltaTimeFUNCTION);
	
	// This is like line 102, but is calling the Lua moveObject() funtion instead
	pBrain->LoadScript("moveBob", "moveObject(50)");

	unsigned int counter = 0;
	while ( true )
	{
		// Pass Lua the current delta (frame) time
		// This will simulate a little bit of variation or "jitter" 
		//	in the delta time
		// Return a value between 10 to 15 ms
		float deltaTime = getRandomFloatInRange(0.01f, 0.015f);
		// Tell Lua about this current frametime
		std::stringstream setDeltaTimeTextScript;
		// Something like this: "deltaTime = 0.0"
		setDeltaTimeTextScript << "deltaTime = " << deltaTime;
		pBrain->RunScriptImmediately( setDeltaTimeTextScript.str() );

		// Update will run any Lua script sitting in the "brain"
		pBrain->Update(1.0);
		
		// See if Bob updated (from Lua)
//		std::cout
//			<< p_Bob->position.x << ", "
//			<< p_Bob->position.y << ", "
//			<< p_Bob->position.z << std::endl;

		counter++;
	}


	delete pBrain;

	return 0;
}



