#pragma once

#include "cCommand.h"
#include "cMeshObject.h"


class cDropShipTakeOff : public cCommand
{
private:
	cDropShipTakeOff() {};	// Can't be called because it's private
public:
	cDropShipTakeOff(cMeshObject* pDropShip);

	virtual void AtStart(void);
	virtual void AtEnd(void);
	virtual bool Update(double deltaTime);
	virtual bool isComplete(void);

private:
	cMeshObject* m_pDropShip;

	// Here's the steps:
	// Turn engines straight down
	// Increase thrust to maximum
	// Slowly lift off (go up) for 5 seconds
	// Start turning engines backwards...
	// ...while we start moving forwards
	enum eStates
	{
		STEP_1_ENGINES_TURNING_DOWN,
		STEP_2_THROTTLEUP_TO_MAX,
		STEP_3_LIFT_OFF,
		STEP_4_ENGINES_TURNING_BACK_MOVING_FORWARD,
		ALL_DONE
	};

	double m_StateCountDownTimer;
	float m_EngineAngle = 0.0f;
	float m_EngineThrust = 0.0f;

	eStates m_CurrentState;
};
