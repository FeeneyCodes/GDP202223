#include "globalOpenGL.h"
#include "globalThings.h"   // For the light manager, etc.
#include <glm/glm.hpp>
#include <glm/vec3.hpp>

// Extern is so the compiler knows what TYPE this thing is
// The LINKER needs the ACTUAL declaration 
// These are defined in theMainFunction.cpp
extern glm::vec3 g_cameraEye;// = glm::vec3(0.0, 0.0, -25.0f);
extern glm::vec3 g_cameraTarget;// = glm::vec3(0.0f, 0.0f, 0.0f);


enum eEditMode
{
    MOVING_CAMERA,
    MOVING_LIGHT,
    MOVING_SELECTED_OBJECT  // For later, maybe??
};

eEditMode theEditMode = MOVING_CAMERA;
unsigned int selectedLightIndex = 0;

bool bEnableDebugLightingObjects = true;


//0000 0001   1	GLFW_MOD_SHIFT
//0000 0010 	  2
//0000 0100   4
//
//0000 0110
//0000 0001 	"Mask"
//-------- -
//0000 0000
//
//// I ONLY want the shift key and nothing else
//if (mods == GLFW_MOD_SHIFT)
//
//// Shift key but I don't care if anything else is down, too
//if ((mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT)


// HACK: Engine thrust (because I don't have a "ship" or actor object...
float g_EngineThrust = 1.0f;

void key_callback(GLFWwindow* window,
                         int key, int scancode,
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    if (key == GLFW_KEY_C && action == GLFW_PRESS)
    {
        theEditMode = MOVING_CAMERA;
    }
    else if (key == GLFW_KEY_L && action == GLFW_PRESS)
    {
        theEditMode = MOVING_LIGHT;

//        // Check for the mods to turn the spheres on or off
//        if ( mods == GLFW_MOD_CONTROL )
//        {
//            bEnableDebugLightingObjects = true;
//        }
//        if ( mods == GLFW_MOD_ALT )
//        {
//            bEnableDebugLightingObjects = false;
//        }
    }

    if (key == GLFW_KEY_9 && action == GLFW_PRESS)
    {
        // Check for the mods to turn the spheres on or off
        bEnableDebugLightingObjects = false;
    }
    if (key == GLFW_KEY_0 && action == GLFW_PRESS)
    {
        // Check for the mods to turn the spheres on or off
        bEnableDebugLightingObjects = true;
    }


    // Move the drop ships engine
    cMeshObject* pDropShipEngine1
        = findObjectByFriendlyName("Engine_1", vec_pMeshObjects);
    
    if ( pDropShipEngine1 )
    {
        if (key == GLFW_KEY_T)     // Rotate one way
        {
//            pDropShipEngine1->rotation.x += glm::radians(1.0f);
            // Now I'm using quaternions
            pDropShipEngine1->adjustRoationAngleFromEuler(glm::vec3(glm::radians(1.0f), 0.0f, 0.0f) );

//            pMediator->RecieveMessage("DropShip Rotate Engine 1", 0.1f);
//            pMediator->RecieveMessage("DSRE1", 0.1f);
//            pMediator->RecieveMessage(2536, 0.1f);
        }
        if (key == GLFW_KEY_Y)     // Rotate the other way
        {
//            pDropShipEngine1->rotation.x -= glm::radians(1.0f);
            // Now I'm using quaternions
            pDropShipEngine1->adjustRoationAngleFromEuler(glm::vec3(glm::radians(-1.0f), 0.0f, 0.0f));
        }
        
    }//if ( pDropShipEngine1 )
    
    // Change the thrust of the engine (by changing the scale of the imposter)
    cMeshObject* pEngine_1_Thrust
        = findObjectByFriendlyName("Engine_1_Thrust", vec_pMeshObjects);
    if (pEngine_1_Thrust)
    {
        if (key == GLFW_KEY_U)     // Decrease the thrust
        {
            ::g_EngineThrust *= 0.99f;      // Decrease by 1%
        }
        if (key == GLFW_KEY_I)     // Increase the thrust
        {
            ::g_EngineThrust *= 1.01f;      // Increase by 1%
        }
        pEngine_1_Thrust->scaleXYZ.z = ::g_EngineThrust;
        // Adjust the thrust a little each frame (so it "flickers" in length)
        pEngine_1_Thrust->scaleXYZ.z += getRandomFloatInRange(-0.1f, 0.1f);

    }//if ( pEngine_1_Thrust )                                                             


    switch (theEditMode)
    {
    case MOVING_CAMERA:
        {
            // Move the camera
            // AWSD   AD - left and right
            //        WS - forward and back
            float CAMERA_MOVE_SPEED = 0.1f;
            // If shift is down, move 10x faster
            // This allows for other mods being down, too
            if ( (mods & GLFW_MOD_SHIFT) == GLFW_MOD_SHIFT )
            {
                CAMERA_MOVE_SPEED *= 1.0f;
            }


            if (key == GLFW_KEY_A)     // Left
            {
                ::g_cameraEye.x -= CAMERA_MOVE_SPEED;
            }
            if (key == GLFW_KEY_D)     // Right
            {
                ::g_cameraEye.x += CAMERA_MOVE_SPEED;
            }
            if (key == GLFW_KEY_W)     // Forward
            {
                ::g_cameraEye.z += CAMERA_MOVE_SPEED;
            }
            if (key == GLFW_KEY_S)     // Backwards
            {
                ::g_cameraEye.z -= CAMERA_MOVE_SPEED;
            }
            if (key == GLFW_KEY_Q)     // Down
            {
                ::g_cameraEye.y -= CAMERA_MOVE_SPEED;
            }
            if (key == GLFW_KEY_E)     // Up
            {
                ::g_cameraEye.y += CAMERA_MOVE_SPEED;
            }

            if (key == GLFW_KEY_1)
            {
                ::g_cameraEye = glm::vec3(-5.5f, -3.4f, 15.0f);
            }
        }//case MOVING_CAMERA:
        break;

    case MOVING_LIGHT:
        {
            const float LIGHT_MOVE_SPEED = 0.1f;
            if (key == GLFW_KEY_A)     // Left
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.x -= LIGHT_MOVE_SPEED;
            }
            if (key == GLFW_KEY_D)     // Right
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.x += LIGHT_MOVE_SPEED;
            }
            if (key == GLFW_KEY_W)     // Forward
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.z += LIGHT_MOVE_SPEED;
            }
            if (key == GLFW_KEY_S)     // Backwards
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.z -= LIGHT_MOVE_SPEED;
            }
            if (key == GLFW_KEY_Q)     // Down
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.y -= LIGHT_MOVE_SPEED;
            }
            if (key == GLFW_KEY_E)     // Up
            {
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].position.y += LIGHT_MOVE_SPEED;
            }

            if (key == GLFW_KEY_PAGE_DOWN)        
            {
                // Select previous light
                if ( selectedLightIndex > 0 )
                {
                    selectedLightIndex--;
                }
            }
            if (key == GLFW_KEY_PAGE_UP)
            {
                if ( selectedLightIndex < (::g_pTheLightManager->vecTheLights.size() - 1) )
                {
                    // Select previous light
                    selectedLightIndex++;
                }
            }

            // Change attenuation
            // Linear is ==> "how bright the light is"
            // Quadratic is ==> "how far does the light go or 'throw' into the scene?"
            if (key == GLFW_KEY_1 )
            {
                // Linear Decrease by 1% 
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.y *= 0.99f;
            }
            if (key == GLFW_KEY_2 )
            {
                // Linear Increase by 1%
                ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.y *= 1.01f;
            }
            if (key == GLFW_KEY_3 )
            {
                if (mods == GLFW_MOD_SHIFT)
                {   // ONLY shift modifier is down
                    // Quadratic Decrease by 0.1% 
                    ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.z *= 0.99f;
                }
                else
                {
                    // Quadratic Decrease by 0.01% 
                    ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.z *= 0.999f;
                }
            }
            if (key == GLFW_KEY_4 )
            {
                if (mods == GLFW_MOD_SHIFT)
                {   // ONLY shift modifier is down
                    // Quadratic Increase by 0.1% 
                    ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.z *= 1.01f;
                }
                else
                {
                    // Quadratic Decrease by 0.01% 
                    ::g_pTheLightManager->vecTheLights[selectedLightIndex].atten.z *= 1.001f;
                }
            }

        }//case MOVING_LIGHT:
        break;

    }//switch (theEditMode)

    return;
}
