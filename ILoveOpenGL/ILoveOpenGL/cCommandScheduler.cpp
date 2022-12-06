#include "cCommandScheduler.h"

cCommandScheduler::cCommandScheduler()
{
}

cCommandScheduler::~cCommandScheduler()
{
	
}

void cCommandScheduler::AddSerialCommandGroup(cCommandGroup* pSerialCommand)
{
	this->vecSerialCommandGroups.push_back(pSerialCommand);
	return;
}

void cCommandScheduler::AddParallelCommandGroup(cCommandGroup* pParallelCommand)
{
	this->vecParallelCommandGroups.push_back(pParallelCommand);
	return;
}

//// This is optional to "nest" commands together
//std::vector< cCommandGroup* > vecSerialCommandGroups;
//std::vector< cCommandGroup* > vecParallelCommandGroups;

void cCommandScheduler::Update(double deltaTime)
{
	// If there's anything in the serial command group, then call update
	if ( ! this->vecSerialCommandGroups.empty() )
	{
		this->vecSerialCommandGroups[0]->Update(deltaTime);
		// Is this command group done?
		if ( this->vecSerialCommandGroups[0]->isDone() )
		{
			// Yes
			this->vecSerialCommandGroups[0]->AtEnd();
			// Delete it
			this->vecSerialCommandGroups.erase(this->vecSerialCommandGroups.begin());
		}
		// Next command? 
		if (!this->vecSerialCommandGroups.empty())
		{
			// Yes
			this->vecSerialCommandGroups[0]->AtStart();
		}
	}// if ( ! this->vecSerialCommandGroups.empty() )

	// RUN all the Parallel commands
	bool bAllCommandsDone = true;	// Assume they are all done
	if ( ! this->vecParallelCommandGroups.empty() )
	{
		for (std::vector< cCommandGroup* >::iterator itCG = this->vecParallelCommandGroups.begin(); 
			 itCG != this->vecParallelCommandGroups.end(); itCG++ )
		{
			cCommandGroup* pCurCG = *itCG;

			if ( ! pCurCG->isDone() )
			{
				pCurCG->Update(deltaTime);
				// At least one of them ISN'T done
				bAllCommandsDone = false;
			}
			else
			{
				// Command done
				pCurCG->AtEnd();
			}
		}
	}//if ( ! this->vecParallelCommandGroups.empty() )

	if (bAllCommandsDone)
	{
		// Delete all the parallel commands
		// Theoretically this is "slow", but there's only a few things on this vector
		// If you want, you can change this to a list or a map (instead of a vector)
		if ( ! this->vecParallelCommandGroups.empty() )
		{
			this->vecParallelCommandGroups.erase(this->vecParallelCommandGroups.begin());
		}
		
	}//if (bAllCommandsDone)

	return;
}


