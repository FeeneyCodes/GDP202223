#pragma once

#include "cCommand.h"
#include <vector>

class cCommandGroup
{
public:
	cCommandGroup();

	void AddSerialCommand(cCommand* pSerialCommand);
	void AddParallelCommand(cCommand* pParallelCommand);

	std::vector< cCommand* > vecSerialCommands;
	std::vector< cCommand* > vecParallelCommands;

//	// This is optional to "nest" commands together
//	std::vector< cCommandGroup* > vecSerialCommandGroups;
//	std::vector< cCommandGroup* > vecParallelCommandGroups;

	void AtStart(void);
	void AtEnd(void);

	// * Run the current serial command (if any)
	// * Run ALL the parallel commands (if any)
	void Update(double deltaTime);
	// Returns true only when ALL the serial commands are done and ALL the parallel commands are done
	bool isDone(void);
};

class cCommandScheduler
{
public:
	cCommandScheduler();
	~cCommandScheduler();

	void AddSerialCommandGroup(cCommandGroup* pSerialCommand);
	void AddParallelCommandGroup(cCommandGroup* pParallelCommand);

	// This is optional to "nest" commands together
	std::vector< cCommandGroup* > vecSerialCommandGroups;
	std::vector< cCommandGroup* > vecParallelCommandGroups;

	void Update(double deltaTime);

};