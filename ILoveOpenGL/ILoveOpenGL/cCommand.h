#pragma once


class cCommand
{
public:
	// This is called once when the command is started
	// Might not do anything
	virtual void AtStart(void) 
	{
		return;
	}
	// This is called once after the command is finished
	// Might not do anything
	virtual void AtEnd(void) {
		return;
	}
	// This is called every frame
	// Returns false when the command is done
	virtual bool Update(double deltaTime) {
		return true;
	}
	// This is also called every frame
	// Returns true when the command is done
	virtual bool isComplete(void)
	{
		return true;
	}

//	// You could also have this Command ALSO act like a command group
//	//	with "nested" commands
//	std::vector< cCommand* > vecSerialCommands;
//	std::vector< cCommand* > vecParallelCommands;


};
