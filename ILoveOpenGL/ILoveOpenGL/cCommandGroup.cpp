#include "cCommandScheduler.h"

cCommandGroup::cCommandGroup()
{

}

void cCommandGroup::AtStart(void)
{
	return;
}

void cCommandGroup::AtEnd(void)
{
	return;
}

// * Run the current serial command (if any)
// * Run ALL the parallel commands (if any)
void cCommandGroup::Update(double deltaTime)
{

	return;
}


// Returns true only when ALL the serial commands are done and ALL the parallel commands are done
bool cCommandGroup::isDone(void)
{
	return true;
}
