#include "cDropShipTakeOff.h"

#include "globalThings.h"		// for getRandom()

cDropShipTakeOff::cDropShipTakeOff(cMeshObject* pDropShip)
{
	this->m_pDropShip = pDropShip;

	this->m_CurrentState = cDropShipTakeOff::STEP_1_ENGINES_TURNING_DOWN;

	this->m_StateCountDownTimer = 5.0;

}

void cDropShipTakeOff::AtStart(void)
{
	return;
}

void cDropShipTakeOff::AtEnd(void)
{
	return;
}

bool cDropShipTakeOff::Update(double deltaTime)
{
	switch (this->m_CurrentState)
	{
	case STEP_1_ENGINES_TURNING_DOWN:
		{
			const float ENGINE_ROTATION_SPEED = 5.0f;	// 2 degrees per second
			float engineAdjustAngleDelta = ENGINE_ROTATION_SPEED * deltaTime;
			this->m_EngineAngle += engineAdjustAngleDelta;
			cMeshObject* pEngine = this->m_pDropShip->findObjectByFriendlyName("Engine_1");
			if ( pEngine )
			{
				pEngine->setRotationFromEuler(glm::vec3(this->m_EngineAngle, 0.0f, 0.0f));
			}
			// Is the engine turned straight down?
			if ( this->m_EngineAngle >= 90.0f )
			{
				// Yes, so go to the next state
				this->m_CurrentState = cDropShipTakeOff::STEP_2_THROTTLEUP_TO_MAX;
			}
		}
		break;
	case STEP_2_THROTTLEUP_TO_MAX:
		{
			cMeshObject* pEngine_1_Thrust = this->m_pDropShip->findObjectByFriendlyName("Engine_1_Thrust");
			if (pEngine_1_Thrust)
			{

				this->m_EngineThrust *= 1.01f;      // Increase by 1%
				pEngine_1_Thrust->scaleXYZ.z = this->m_EngineThrust;
				// Adjust the thrust a little each frame (so it "flickers" in length)
				pEngine_1_Thrust->scaleXYZ.z += getRandomFloatInRange(-0.1f, 0.1f);
				// All done? 
				if ( this->m_EngineThrust >= 3.0f )
				{
					// Yup.
					this->m_CurrentState = cDropShipTakeOff::STEP_3_LIFT_OFF;
				}
			}
		}
		break;
	case STEP_3_LIFT_OFF:
		// HACK
		this->m_CurrentState = cDropShipTakeOff::ALL_DONE;

		break;
	case STEP_4_ENGINES_TURNING_BACK_MOVING_FORWARD:
		break;
	case ALL_DONE:
		
		return false;
		break;
	};//switch (this->m_CurrentState)


	// Uprate worked (i.e. it's still doing whatever it is that it's supposed to be doing...)
		return true;
}

bool cDropShipTakeOff::isComplete(void)
{
	if ( this->m_CurrentState == cDropShipTakeOff::ALL_DONE )
	{
		return true;
	}
	return false;
}
