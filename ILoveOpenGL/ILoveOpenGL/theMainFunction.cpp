
//#include <glad/glad.h>
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
#include "globalOpenGL.h"

//#include "linmath.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3        (x,y,z)
#include <glm/vec4.hpp> // glm::vec4        (x,y,z,w)
#include <glm/mat4x4.hpp> // glm::mat4
// glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>  // File streaming thing (like cin, etc.)
#include <sstream>  // "string builder" type thing

// Some STL (Standard Template Library) things
#include <vector>           // aka a "smart array"

#include "globalThings.h"

#include "cShaderManager.h"
#include "cVAOManager/cVAOManager.h"
#include "cLightHelper.h"
#include "cVAOManager/c3DModelFileLoader.h"


// This is all now part of the VAO manager
// 
//struct sVertex_XYZ_RGB
//{
//    float x, y, z;             // 0 floats from the start
//    float r, g, b;          // 2 floats from the start
//                     // Each vertex is 5 floats in size
//};
//
//struct sVertex_XYZ_N_RGBA_UV
//{
//    float x, y, z;
//    float nx, ny, nz;
//    //uchar red, green, blue, alpha;
//    float red, green, blue, alpha;
//    float texture_u, texture_v;
//};
//
//struct sTrianglePLY
//{
//    // The 3 vertex index values from the ply file
//    unsigned int vertexIndices[3];
//};
//
//// The ply file info gets copied into one of these
//struct sPLYFileInfo
//{
//    // Array we will load into
//    sVertex_XYZ_N_RGBA_UV* pTheModelArray = NULL;   // NULL, 0, nullptr
//    sTrianglePLY* pTheModelTriangleArray = NULL;
//
//    unsigned int numberOfvertices = 0;
//    unsigned int numberOfTriangles = 0;
//
//    // This is the data we are copying to the GPU 
//    sVertex_XYZ_RGB* vertices = NULL;
//    unsigned int numberOfVerticesToDraw = 0;
//};

//sVertex_XYZ_RGB vertices[] =
//{
//        { -0.6f, -0.4f, 0.0, 1.0f, 0.0f, 0.0f },
//        {  0.6f, -0.4f, 0.0, 0.0f, 1.0f, 0.0f },
//        {  0.0f,  0.6f, 0.0, 0.0f, 0.0f, 1.0f },
//
//        { (-0.6f + 1.0f), -0.4f, 0.0,  0.0f, 1.0f, 0.0f },
//        {  (0.6f + 1.0f), -0.4f, 0.0,  0.0f, 0.0f, 1.0f },
//        {  (0.0f + 1.0f),  0.6f, 0.0,  1.0f, 0.0f, 0.0f }
//};

//const unsigned int NUMBER_OF_VERTICES = 100;
//
//sVertex_XYZ_RGB* vertices = new sVertex_XYZ_RGB[NUMBER_OF_VERTICES];

glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, -25.0f);
glm::vec3 g_cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);




//static const char* vertex_shader_text =
//"#version 110\n"
//"uniform mat4 MVP;\n"
//"attribute vec3 vCol;\n"
//"attribute vec3 vPos;\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = MVP * vec4(vPos, 1.0);\n"
//"    color = vCol;\n"
//"}\n";
//
//static const char* fragment_shader_text =
//"#version 110\n"
//"varying vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_FragColor = vec4(color, 1.0);\n"
//"}\n";

// Call back signatures here
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}


// From here: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624

float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}


// This code is now in the c3DModelFileLoader class
//bool LoadThePLYFile(std::string filename, sModelDrawInfo &modelDrawInfo)
//{
//    struct sVertex_XYZ_N_RGBA_UV
//    {
//        float x, y, z;
//        float nx, ny, nz;
//        //uchar red, green, blue, alpha;
//        float red, green, blue, alpha;
//        float texture_u, texture_v;
//    };
//
//    struct sTrianglePLY
//    {
//        // The 3 vertex index values from the ply file
//        unsigned int vertexIndices[3];
//    };
//
//    // Array we will load into
//   sVertex_XYZ_N_RGBA_UV* pTheModelArray = NULL;   // NULL, 0, nullptr
//   sTrianglePLY* pTheModelTriangleArray = NULL;
////    unsigned int numberOfvertices = 0;
////    unsigned int numberOfTriangles = 0;
//
//    // Start loading the file
//
//    std::ifstream theFile(filename);
//    if ( ! theFile.is_open() )
//    {
//        std::cout << "Didn't open it!" << std::endl;
//        return false;
//    }
//
//    // Read an entire line
//    char buffer[10000];
//    theFile.getline(buffer, 10000);
// 
//    std::string theNextToken;
//
//    // Scan for the word "vertex"
//    while ( theFile >> theNextToken )
//    {
//        if ( theNextToken == "vertex" )
//        {
//            break;
//        }
//    }
//    // 
//    theFile >> modelDrawInfo.numberOfVertices;
//
//    // Scan for the word "face"
//    while (theFile >> theNextToken)
//    {
//        if (theNextToken == "face")
//        {
//            break;
//        }
//    }
//    // 
//    theFile >> modelDrawInfo.numberOfTriangles;
//
//    // Scan for the word "end_header"
//    while (theFile >> theNextToken)
//    {
//        if (theNextToken == "end_header")
//        {
//            break;
//        }
//    }
//
//    // Now we load the vertices
//    // -0.036872 0.127727 0.00440925 0.2438786 0.9638011 -0.1077533 127 127 127 255 0.337485 0.8899501
//
//    pTheModelArray = new sVertex_XYZ_N_RGBA_UV[modelDrawInfo.numberOfVertices];
//
//    std::cout << "Loading";
//    for ( unsigned int count = 0; count != modelDrawInfo.numberOfVertices; count++ )
//    {
//        theFile >> pTheModelArray[count].x;
//        theFile >> pTheModelArray[count].y;
//        theFile >> pTheModelArray[count].z;
//
//        theFile >> pTheModelArray[count].nx;
//        theFile >> pTheModelArray[count].ny;
//        theFile >> pTheModelArray[count].nz;
//
//        theFile >> pTheModelArray[count].red;
//        theFile >> pTheModelArray[count].green;
//        theFile >> pTheModelArray[count].blue;
//        theFile >> pTheModelArray[count].alpha;
//
//        theFile >> pTheModelArray[count].texture_u;
//        theFile >> pTheModelArray[count].texture_v;
//
//        if ( count % 10000 == 0 )
//        {
//            std::cout << ".";
//        }
//   }
//    std::cout << "done" << std::endl;
//
//
//    // HACK: "Transform" the model here
//    for (unsigned int count = 0; count != modelDrawInfo.numberOfVertices; count++)
//    {
////        pTheModelArray[count].x *= 0.1f;
////        pTheModelArray[count].y *= 0.1f;
////        pTheModelArray[count].z *= 0.1f;
//
////        pTheModelArray[count].x += 20.0f;
//    }
//
//
//    // Load the faces (or triangles)
//    pTheModelTriangleArray = new sTrianglePLY[modelDrawInfo.numberOfTriangles];
//
//    for ( unsigned int count = 0; count != modelDrawInfo.numberOfTriangles; count++ )
//    {
//        // 3 15393 15394 15395 
//        unsigned int discard = 0;
//        theFile >> discard;
//
//        theFile >> pTheModelTriangleArray[count].vertexIndices[0];
//        theFile >> pTheModelTriangleArray[count].vertexIndices[1];
//        theFile >> pTheModelTriangleArray[count].vertexIndices[2];
//    }
//
//    theFile.close();
//
//    // This is now different because the vertex layout in the shader is different
//    modelDrawInfo.pVertices = new sVertex_RGBA_XYZ_N_UV_T_BiN_Bones[modelDrawInfo.numberOfVertices];
////    modelDrawInfo.pVertices = new sVertex[modelDrawInfo.numberOfVertices];
//
//    // Now copy the information from the PLY infomation to the model draw info structure
//    for ( unsigned int index = 0; index != modelDrawInfo.numberOfVertices; index++ )
//    {
//        // To The Shader                        From the file
//        modelDrawInfo.pVertices[index].x = pTheModelArray[index].x;
//        modelDrawInfo.pVertices[index].y = pTheModelArray[index].y;
//        modelDrawInfo.pVertices[index].z = pTheModelArray[index].z;
//
//        modelDrawInfo.pVertices[index].r = pTheModelArray[index].red;
//        modelDrawInfo.pVertices[index].g = pTheModelArray[index].green;
//        modelDrawInfo.pVertices[index].b = pTheModelArray[index].blue;
//
//        // Copy the normal information we loaded, too! :)
//        modelDrawInfo.pVertices[index].nx = pTheModelArray[index].nx;
//        modelDrawInfo.pVertices[index].ny = pTheModelArray[index].ny;
//        modelDrawInfo.pVertices[index].nz = pTheModelArray[index].nz;
//
//    }
//
//    modelDrawInfo.numberOfIndices = modelDrawInfo.numberOfTriangles * 3;
//
//    // This is the "index" (or element) buffer
//    modelDrawInfo.pIndices = new unsigned int[modelDrawInfo.numberOfIndices];
//
//    unsigned int vertex_element_index_index = 0;
//
//    for ( unsigned int triangleIndex = 0; triangleIndex != modelDrawInfo.numberOfTriangles; triangleIndex++ )
//    {
//        modelDrawInfo.pIndices[vertex_element_index_index + 0] = pTheModelTriangleArray[triangleIndex].vertexIndices[0];
//        modelDrawInfo.pIndices[vertex_element_index_index + 1] = pTheModelTriangleArray[triangleIndex].vertexIndices[1];
//        modelDrawInfo.pIndices[vertex_element_index_index + 2] = pTheModelTriangleArray[triangleIndex].vertexIndices[2];
//
//        // Each +1 of the triangle index moves the "vertex element index" by 3
//        // (3 vertices per triangle)
//        vertex_element_index_index += 3;
//    }
//
//    delete [] pTheModelArray;   
//    delete [] pTheModelTriangleArray;
//
//
//    return true;
//}



bool LoadModelTypesIntoVAO(std::string fileTypesToLoadName, 
                           cVAOManager* pVAOManager, 
                           GLuint shaderID)
{
    std::ifstream modelTypeFile( fileTypesToLoadName.c_str() );
    if ( ! modelTypeFile.is_open() )
    {
        // Can't find that file
        return false;
    }

    // At this point, the file is open and ready for reading

    std::string PLYFileNameToLoad;     // = "assets/models/MOTO/Blender (load from OBJ export) - only Moto_xyz_n_rgba_uv.ply";
    std::string friendlyName;   // = "MOTO";

    bool bKeepReadingFile = true;

    const unsigned int BUFFER_SIZE = 1000;  // 1000 characters
    char textBuffer[BUFFER_SIZE];       // Allocate AND clear (that's the {0} part)
    // Clear that array to all zeros
    memset(textBuffer, 0, BUFFER_SIZE);

    // Or if it's integers, you can can do this short cut:
    // char textBuffer[BUFFER_SIZE] = { 0 };       // Allocate AND clear (that's the {0} part)

    while ( bKeepReadingFile )
    {
        // Reads the entire line into the buffer (including any white space)
        modelTypeFile.getline(textBuffer, BUFFER_SIZE);

        PLYFileNameToLoad.clear();  // Erase whatever is already there (from before)
        PLYFileNameToLoad.append(textBuffer);

        // Is this the end of the file (have I read "EOF" yet?)?
        if ( PLYFileNameToLoad == "EOF" )
        {
            // All done
            bKeepReadingFile = false;
            // Skip to the end of the while loop
            continue;
        }

        // Load the "friendly name" line also

        memset(textBuffer, 0, BUFFER_SIZE);
        modelTypeFile.getline(textBuffer, BUFFER_SIZE);
        friendlyName.clear();
        friendlyName.append(textBuffer);

        sModelDrawInfo motoDrawInfo;

        c3DModelFileLoader fileLoader;
        //if (LoadThePLYFile(PLYFileNameToLoad, motoDrawInfo))
        std::string errorText = "";
        if (fileLoader.LoadPLYFile_Format_XYZ_N_RGBA_UV(PLYFileNameToLoad, motoDrawInfo, errorText))
        {
            std::cout << "Loaded the file OK" << std::endl;
        }
        else
        {
            std::cout << errorText;
        }

        if (pVAOManager->LoadModelIntoVAO(friendlyName, motoDrawInfo, shaderID))
        {
            std::cout << "Loaded the MOTO model" << std::endl;
        }

    }//while (modelTypeFile

    return true;
}

bool SaveTheVAOModelTypesToFile(std::string fileTypesToLoadName,
                                cVAOManager* pVAOManager);


void DrawConcentricDebugLightObjects(void);

// HACK: These are the light spheres we will use for debug lighting
cMeshObject* pDebugSphere_1 = NULL;// = new cMeshObject();
cMeshObject* pDebugSphere_2 = NULL;// = new cMeshObject();
cMeshObject* pDebugSphere_3 = NULL;// = new cMeshObject();
cMeshObject* pDebugSphere_4 = NULL;// = new cMeshObject();
cMeshObject* pDebugSphere_5 = NULL;// = new cMeshObject();

int main( int argc, char* argv[] )
{
//    sPLYFileInfo thePlyInfo;
//    std::string fileToLoad = "assets/models/BirdOfPrey/BirdOfPrey_Exported.ply";
//    std::string fileToLoad = "assets/models/MOTO/Blender (load from OBJ export) - only Moto_xyz_n_rgba_uv.ply";
//    std::string fileToLoad = "assets/models/bunny/reconstruction/bun_zipper_res2_xyz_n_rgba_uv.ply";
//    if ( LoadTheFile(fileToLoad, thePlyInfo) )
//    {
//        std::cout << "Loaded the file OK" << std::endl;
//    }
//
 //   sPLYFileInfo thePlyInfo_Motorcycle;
 //   sPLYFileInfo thePlyInfo_BirdOfPrey;
//
//    sPLYFileInfo theModelsWeCanDraw[100];
//    std::vector<sPLYFileInfo> vecAllTheModelsWeCanDraw;
//
//
    // Copy the file data I loaded into the array that the shader expects
//    thePlyInfo.vertices = new sVertex_XYZ_RGB[thePlyInfo.numberOfvertices];
//
//    for ( unsigned int index = 0; index != thePlyInfo.numberOfvertices; index++ )
//    {
//        thePlyInfo.vertices[index].x = thePlyInfo.pTheModelArray[index].x;
//        thePlyInfo.vertices[index].y = thePlyInfo.pTheModelArray[index].y;
//        thePlyInfo.vertices[index].z = thePlyInfo.pTheModelArray[index].z;
//
//        thePlyInfo.vertices[index].r = thePlyInfo.pTheModelArray[index].red;
//        thePlyInfo.vertices[index].g = thePlyInfo.pTheModelArray[index].green;
//        thePlyInfo.vertices[index].b = thePlyInfo.pTheModelArray[index].blue;
//    }
//
//
//    // Vertices we want to DRAW is number of triangles * 3
//    unsigned int numVerticesToDraw = thePlyInfo.numberOfTriangles * 3;
//    thePlyInfo.vertices = new sVertex_XYZ_RGB[numVerticesToDraw];
//
//    unsigned int vertexIndex = 0;
//    for ( unsigned int triangleIndex = 0; triangleIndex != thePlyInfo.numberOfTriangles; triangleIndex++ )
//    {
//        // copy the 3 vertices form the trianle information, and look up the actual vertex
//
//        unsigned int vert0Index = thePlyInfo.pTheModelTriangleArray[triangleIndex].vertexIndices[0];
//
//        thePlyInfo.vertices[vertexIndex + 0].x = thePlyInfo.pTheModelArray[vert0Index].x;
//        thePlyInfo.vertices[vertexIndex + 0].y = thePlyInfo.pTheModelArray[vert0Index].y;
//        thePlyInfo.vertices[vertexIndex + 0].z = thePlyInfo.pTheModelArray[vert0Index].z;
//        thePlyInfo.vertices[vertexIndex + 0].r = thePlyInfo.pTheModelArray[vert0Index].red;
//        thePlyInfo.vertices[vertexIndex + 0].g = thePlyInfo.pTheModelArray[vert0Index].green;
//        thePlyInfo.vertices[vertexIndex + 0].b = thePlyInfo.pTheModelArray[vert0Index].blue;
//
//        unsigned int vert1Index = thePlyInfo.pTheModelTriangleArray[triangleIndex].vertexIndices[1];
//
//        thePlyInfo.vertices[vertexIndex + 1].x = thePlyInfo.pTheModelArray[vert1Index].x;
//        thePlyInfo.vertices[vertexIndex + 1].y = thePlyInfo.pTheModelArray[vert1Index].y;
//        thePlyInfo.vertices[vertexIndex + 1].z = thePlyInfo.pTheModelArray[vert1Index].z;
//        thePlyInfo.vertices[vertexIndex + 1].r = thePlyInfo.pTheModelArray[vert1Index].red;
//        thePlyInfo.vertices[vertexIndex + 1].g = thePlyInfo.pTheModelArray[vert1Index].green;
//        thePlyInfo.vertices[vertexIndex + 1].b = thePlyInfo.pTheModelArray[vert1Index].blue;
//
//        unsigned int vert2Index = thePlyInfo.pTheModelTriangleArray[triangleIndex].vertexIndices[2];
//
//        thePlyInfo.vertices[vertexIndex + 2].x = thePlyInfo.pTheModelArray[vert2Index].x;
//        thePlyInfo.vertices[vertexIndex + 2].y = thePlyInfo.pTheModelArray[vert2Index].y;
//        thePlyInfo.vertices[vertexIndex + 2].z = thePlyInfo.pTheModelArray[vert2Index].z;
//        thePlyInfo.vertices[vertexIndex + 2].r = thePlyInfo.pTheModelArray[vert2Index].red;
//        thePlyInfo.vertices[vertexIndex + 2].g = thePlyInfo.pTheModelArray[vert2Index].green;
//        thePlyInfo.vertices[vertexIndex + 2].b = thePlyInfo.pTheModelArray[vert2Index].blue;
//
//
//        // increment the vertex values by 3
//        vertexIndex += 3;
//
//    }




//    // Create a bunch of random triangles
//    for ( unsigned int index = 0; index != NUMBER_OF_VERTICES; index++ )
//    {
//        vertices[index].x = RandomFloat(-50.0f, 50.0f);
//        vertices[index].y = RandomFloat(-50.0f, 50.0f);
//        vertices[index].z = RandomFloat(-50.0f, 50.0f);
//
//        vertices[index].r = RandomFloat(0.0f, 1.0f);
//        vertices[index].g = RandomFloat(0.0f, 1.0f);
//        vertices[index].b = RandomFloat(0.0f, 1.0f);
//    }

    std::cout << "starting up..." << std::endl;

    GLFWwindow* window;
    GLuint vertex_buffer = 0;
//    GLuint vertex_shader = 0;
//    GLuint fragment_shader = 0;
//    GLuint program = 0;

    GLuint shaderID = 0;

//    GLint mvp_location = 0;
    GLint vpos_location = 0;
    GLint vcol_location = 0;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window = glfwCreateWindow(640, 480, "Hello Kitty", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    std::cout << "Window created." << std::endl;



    glfwSetKeyCallback(window, key_callback);

    glfwMakeContextCurrent(window);
 //   gladLoadGL( (GLADloadproc)glfwGetProcAddress );
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity
    //int x = 9;              // Location 7363
    //int* px = &x;           // px = 7363
    //int* pX1 = &x;          // px1 = 7363
    //void* pZ = &x;         
    //pZ = RandomFloat;

    //std::cout << pZ; 





//    // Defining the 3D model that we are going to draw. 
//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//
//    unsigned int vertexBufferSizeInBytes 
//        = sizeof(sVertex_XYZ_RGB) * numVerticesToDraw;
////    unsigned int vertexBufferSizeInBytes 
////        = sizeof(thePlyInfo.vertices) * thePlyInfo.numberOfvertices;
//
////    unsigned int vertexBufferSizeInBytes = sizeof(vertices) * NUMBER_OF_VERTICES;
//    glBufferData(GL_ARRAY_BUFFER, 
//                 vertexBufferSizeInBytes, 
//                 thePlyInfo.vertices,              // (void*)
//                 GL_STATIC_DRAW);
////    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Create a shader thingy
    cShaderManager* pTheShaderManager = new cShaderManager();

    cShaderManager::cShader vertexShader01;
    cShaderManager::cShader fragmentShader01;

    vertexShader01.fileName = "assets/shaders/vertexShader01.glsl";
    fragmentShader01.fileName = "assets/shaders/fragmentShader01.glsl";

    if ( ! pTheShaderManager->createProgramFromFile("Shader_1", vertexShader01, fragmentShader01) )
    {
        std::cout << "Didn't compile shaders" << std::endl;
        std::string theLastError = pTheShaderManager->getLastError();
        std::cout << "Because: " << theLastError << std::endl;
        return -1;
    }
    else 
    {
        std::cout << "Compiled shader OK." << std::endl;
    }

    pTheShaderManager->useShaderProgram("Shader_1");

    shaderID = pTheShaderManager->getIDFromFriendlyName("Shader_1");

    glUseProgram(shaderID);




    ::g_pTheLightManager = new cLightManager();

    cLightHelper* pLightHelper = new cLightHelper();

// Set up the uniform variable (from the shader
    ::g_pTheLightManager->LoadLightUniformLocations(shaderID);

    // Set the light information for light #0
//    GLint light_0_position_UL = glGetUniformLocation(shaderID, "theLights[0].position");
//    GLint light_0_diffuse_UL = glGetUniformLocation(shaderID, "theLights[0].diffuse");
//    GLint light_0_specular_UL = glGetUniformLocation(shaderID, "theLights[0].specular");
//    GLint light_0_atten_UL = glGetUniformLocation(shaderID, "theLights[0].atten");
//    GLint light_0_direction_UL = glGetUniformLocation(shaderID, "theLights[0].direction");
//    GLint light_0_param1_UL = glGetUniformLocation(shaderID, "theLights[0].param1");
//    GLint light_0_param2_UL = glGetUniformLocation(shaderID, "theLights[0].param2");

    ::g_pTheLightManager->vecTheLights[0].position = glm::vec4(10.0f, 10.0f, 0.0f, 1.0f);
    ::g_pTheLightManager->vecTheLights[0].diffuse = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ::g_pTheLightManager->vecTheLights[0].atten = glm::vec4(0.1f, 0.01f, 0.0000001f, 1.0f);

//    ::g_pTheLightManager->vecTheLights[0].param2.x = 1.0f;
    ::g_pTheLightManager->vecTheLights[0].TurnOn();

    // Make this a spot light
//    vec4 param1;	// x = lightType, y = inner angle, z = outer angle, w = TBD
//                    // 0 = pointlight
//                    // 1 = spot light
//                    // 2 = directional light
    ::g_pTheLightManager->vecTheLights[0].param1.x = 1.0f;  // 1 means spot light
    
    // In the shader Feeney gave you, the direciton is relative
    ::g_pTheLightManager->vecTheLights[0].direction = glm::vec4(0.0f, -1.0f, 0.0f, 1.0f);
    // inner and outer angles
    ::g_pTheLightManager->vecTheLights[0].param1.y = 10.0f;     // Degrees
    ::g_pTheLightManager->vecTheLights[0].param1.z = 20.0f;     // Degrees


//    glUniform4f(light_0_position_UL, 20.0f, 40.0f, -20.0f, 1.0f);
//    glUniform4f(light_0_diffuse_UL, 1.0f, 1.0f, 1.0f, 1.0f);
//    glUniform4f(light_0_specular_UL, 1.0f, 1.0f, 1.0f, 1.0f);
//    glUniform4f(light_0_atten_UL, 0.1f, 0.01f, 0.0f, 1.0f);
//    glUniform4f(light_0_direction_UL, 0.0f, 0.0f, 0.0f, 1.0f);
//    glUniform4f(light_0_param1_UL, 0.0f /*point light*/, 0.0f, 0.0f, 1.0f);
//    // Turn the light on
//    glUniform4f(light_0_param2_UL, 1.0f, 0.0f, 0.0f, 1.0f);
//
//    glm::vec3 lightPosition = glm::vec3(-30.0f, 50.0f, 0.0f);
//    glUniform4f(light_0_position_UL,
//                lightPosition.x,
//                lightPosition.y,
//                lightPosition.z,
//                1.0f);



    // Load the models
    cVAOManager* pVAOManager = new cVAOManager();

    if ( ! LoadModelTypesIntoVAO("assets/PLYFilesToLoadIntoVAO.txt", pVAOManager, shaderID) )
    {
        std::cout << "Error: Unable to load list of models to load into VAO file" << std::endl;
        // Do we exit here? 
        // (How do we clean up stuff we've made, etc.)
    }//if (!LoadModelTypesIntoVAO...


// **************************************************************************************
// START OF: LOADING the file types into the VAO manager:
/*
    sModelDrawInfo motoDrawInfo;

    std::string fileToLoad = "assets/models/MOTO/Blender (load from OBJ export) - only Moto_xyz_n_rgba_uv.ply";
    if (LoadThePLYFile(fileToLoad, motoDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("MOTO", motoDrawInfo, shaderID))
    {
        std::cout << "Loaded the MOTO model" << std::endl;
    }


    sModelDrawInfo bunnyDrawInfo;
    fileToLoad = "assets/models/bunny/reconstruction/bun_zipper_res2_xyz_n_rgba_uv.ply";
    if (LoadThePLYFile(fileToLoad, bunnyDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("Bunny", bunnyDrawInfo, shaderID))
    {
        std::cout << "Loaded the Bunny model" << std::endl;
    } 
    

    sModelDrawInfo BOPDrawInfo;
    fileToLoad = "assets/models/BirdOfPrey/BirdOfPrey_Exported.ply";
    if (LoadThePLYFile(fileToLoad, BOPDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("BirdOfPrey", BOPDrawInfo, shaderID))
    {
        std::cout << "Loaded the BirdOfPrey model" << std::endl;
    } 
*/
// END OF: LOADING the file types into the VAO manager
// **************************************************************************************
    
    // On the heap (we used new and there's a pointer)
    cMeshObject* pObjectToDraw = new cMeshObject();
    pObjectToDraw->meshName = "MOTO";
    pObjectToDraw->position = glm::vec3(-10.0f, 0.0f, 0.0f);

    cMeshObject* pBunnyObjectToDraw1 = new cMeshObject();
    pBunnyObjectToDraw1->meshName = "Bunny";
    pBunnyObjectToDraw1->friendlyName = "Bugs";         // Google "Bugs Bunny"
    pBunnyObjectToDraw1->position = glm::vec3(0.0f, -2.0f, 0.0f);
//    pBunnyObjectToDraw1->scale = 1.0f;

    cMeshObject* pBunnyObjectToDraw2 = new cMeshObject();
    pBunnyObjectToDraw2->meshName = "Bunny";
    pBunnyObjectToDraw2->position = glm::vec3(2.0f, -2.0f, 0.0f);
//   pBunnyObjectToDraw2->scale = 1.0f;

    cMeshObject* pSpaceShip = new cMeshObject();
    pSpaceShip->meshName = "BirdOfPrey";

    cMeshObject* pSubmarine = new cMeshObject();
    pSubmarine->meshName = "Submarine";
    pSubmarine->position = glm::vec3(10.0f, 0.0f, 0.0f);
//    pSubmarine->scale = 1.0f;
    pSubmarine->rotation.y = glm::radians(-15.0f);

    cMeshObject* pYellowSubmarine = new cMeshObject();
    pYellowSubmarine->meshName = "Submarine";
    pYellowSubmarine->friendlyName = "Yellow Submarine";    // Google "Yellow Submarine" to see what drugs in the 60s were like.
    pYellowSubmarine->bUse_RGBA_colour = true;
    pYellowSubmarine->RGBA_colour = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
//    pYellowSubmarine->isWireframe = true;

    cMeshObject* pTerrain = new cMeshObject();
    pTerrain->meshName = "Terrain";
    pTerrain->friendlyName = "Terrain";
    pTerrain->bUse_RGBA_colour = false;
    pTerrain->position = glm::vec3(0.0f, -25.0f, -50.0f);
//    pYellowSubmarine->isWireframe = true;



//    // Add all these to an array:
//    cMeshObject* my_pMeshes[10];
//    my_pMeshes[0] = pObjectToDraw;          // "MOTO"
//    my_pMeshes[1] = pBunnyObjectToDraw1;    // "Bunny"
//    my_pMeshes[2] = pBunnyObjectToDraw2;    // "Bunny"
//    my_pMeshes[3] = pSpaceShip;    // "BirdOfPrey"
//    my_pMeshes[4] = pSubmarine;    // "Submarine"
////    my_pMeshes[4] = ??? 
// 
//     Now I want "Homer Simpson" at index #0
//
//    unsigned int numberOfObjectsToDraw = 5;

    // Which is the equivalent to:
    //    cMeshObject* my_pMeshes[10];
    std::vector< cMeshObject* > vec_pMeshObjects;


    vec_pMeshObjects.push_back(pObjectToDraw);          // "MOTO"
    vec_pMeshObjects.push_back(pBunnyObjectToDraw1);    // "Bunny"
    vec_pMeshObjects.push_back(pBunnyObjectToDraw2);    // "Bunny"
    vec_pMeshObjects.push_back(pSpaceShip);    // "BirdOfPrey"
    vec_pMeshObjects.push_back(pSubmarine);    // "BirdOfPrey"
    vec_pMeshObjects.push_back(pYellowSubmarine);    // "BirdOfPrey"
    vec_pMeshObjects.push_back(pTerrain);    // "BirdOfPrey"


    pDebugSphere_1 = new cMeshObject();
    pDebugSphere_1->meshName = "ISO_Sphere_1";
    pDebugSphere_1->friendlyName = "Debug Sphere 1";
    pDebugSphere_1->bUse_RGBA_colour = true;
    pDebugSphere_1->RGBA_colour = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    pDebugSphere_1->isWireframe = true;
    pDebugSphere_1->scale = 1.0f;

    pDebugSphere_1->bDoNotLight = true;

    vec_pMeshObjects.push_back(pDebugSphere_1);

    pDebugSphere_2 = new cMeshObject();
    pDebugSphere_2->meshName = "ISO_Sphere_1";
    pDebugSphere_2->friendlyName = "Debug Sphere 2";
    pDebugSphere_2->bUse_RGBA_colour = true;
    pDebugSphere_2->RGBA_colour = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    pDebugSphere_2->isWireframe = true;
    pDebugSphere_2->scale = 1.0f;
    pDebugSphere_2->bDoNotLight = true;
    vec_pMeshObjects.push_back(pDebugSphere_2);

    pDebugSphere_3 = new cMeshObject();
    pDebugSphere_3->meshName = "ISO_Sphere_1";
    pDebugSphere_3->friendlyName = "Debug Sphere 3";
    pDebugSphere_3->bUse_RGBA_colour = true;
    pDebugSphere_3->RGBA_colour = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    pDebugSphere_3->isWireframe = true;
    pDebugSphere_3->scale = 1.0f;
    pDebugSphere_3->bDoNotLight = true;
    vec_pMeshObjects.push_back(pDebugSphere_3);

    pDebugSphere_4 = new cMeshObject();
    pDebugSphere_4->meshName = "ISO_Sphere_1";
    pDebugSphere_4->friendlyName = "Debug Sphere 4";
    pDebugSphere_4->bUse_RGBA_colour = true;
    pDebugSphere_4->RGBA_colour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    pDebugSphere_4->isWireframe = true;
    pDebugSphere_4->scale = 1.0f;
    pDebugSphere_4->bDoNotLight = true;
    vec_pMeshObjects.push_back(pDebugSphere_4);

    pDebugSphere_5 = new cMeshObject();
    pDebugSphere_5->meshName = "ISO_Sphere_1";
    pDebugSphere_5->friendlyName = "Debug Sphere 5";
    pDebugSphere_5->bUse_RGBA_colour = true;
    pDebugSphere_5->RGBA_colour = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
    pDebugSphere_5->isWireframe = true;
    pDebugSphere_5->scale = 1.0f;
    pDebugSphere_5->bDoNotLight = true;
    vec_pMeshObjects.push_back(pDebugSphere_5);


/*  We could also make this on the stack in this way:

    cMeshObject objectToDraw;
    objectToDraw.meshName = "MOTO";

    cMeshObject myMeshes[10];
    myMeshes[0] = objectToDraw;     // Copies it! 

    objectToDraw.meshName = "Bunny";    // Changes this one, but NOT the one in the array

*/


    // Shader setup
//    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//    glCompileShader(vertex_shader);
// 
//    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//    glCompileShader(fragment_shader);
//
//    program = glCreateProgram();
//
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//
//    glLinkProgram(program);
//
//    glUseProgram(program);
//
 //   // Vertex layout
 //   vpos_location = glGetAttribLocation(shaderID, "vPos");   // Vertex Position
 //   vcol_location = glGetAttribLocation(shaderID, "vCol");
 //
 //   glEnableVertexAttribArray(vpos_location);
 //   glVertexAttribPointer(vpos_location,
 //                         3,
 //                         GL_FLOAT,
 //                         GL_FALSE,
 //                         sizeof(sVertex_XYZ_RGB),   //  sizeof(vertices[0]),
 //                         (void*) offsetof(sVertex_XYZ_RGB, x));      //0);
 //
 //   glEnableVertexAttribArray(vcol_location);
 //   glVertexAttribPointer(vcol_location, 
 //                         3, 
 //                         GL_FLOAT, 
 //                         GL_FALSE,
 //                         sizeof(sVertex_XYZ_RGB),               //  sizeof(vertices[0]),
 //                         (void*) offsetof(sVertex_XYZ_RGB, r)); //  (sizeof(float) * 3));


    GLint mvp_location = glGetUniformLocation(shaderID, "MVP");       // program
    // uniform mat4 mModel;
    // uniform mat4 mView;
    // uniform mat4 mProjection;
    GLint mModel_location = glGetUniformLocation(shaderID, "mModel");      
    GLint mView_location = glGetUniformLocation(shaderID, "mView");      
    GLint mProjection_location = glGetUniformLocation(shaderID, "mProjection");       
    // Need this for lighting
    GLint mModelInverseTransform_location = glGetUniformLocation(shaderID, "mModelInverseTranspose");      



    while ( ! glfwWindowShouldClose(window) )
    {
        // HACK
//        ::g_pTheLightManager->vecTheLights[0].position.x += 0.05f;

        ::g_pTheLightManager->CopyLightInformationToShader(shaderID);

//        glUniform4f(light_0_position_UL,
//                    lightPosition.x,
//                    lightPosition.y,
//                    lightPosition.z,
//                    1.0f);


        // Point the spotlight at the submarine
        glm::vec3 LightToSubRay =
            pYellowSubmarine->position - glm::vec3(::g_pTheLightManager->vecTheLights[0].position);

        // Normalizing is also just divide by the length of the ray
//        LightToSubRay /= glm::length(LightToSubRay);
        LightToSubRay = glm::normalize(LightToSubRay);

//        ::g_pTheLightManager->vecTheLights[0].direction = glm::vec4(LightToSubRay, 1.0f);


        DrawConcentricDebugLightObjects();

        float ratio;
        int width, height;
//        mat4x4 m, p, mvp;
        glm::mat4x4 matModel;
        glm::mat4x4 matProjection;
        glm::mat4x4 matView; 

//        glm::mat4x4 mvp;            // Model-View-Projection

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        // note the binary OR (not the usual boolean "or" comparison)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glClear(GL_COLOR_BUFFER_BIT);


        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

        matView = glm::lookAt(::g_cameraEye,
                              ::g_cameraTarget,
                              upVector);

        // Pass eye location to the shader
        // uniform vec4 eyeLocation;
        GLint eyeLocation_UniLoc = glGetUniformLocation(shaderID, "eyeLocation");

        glUniform4f(eyeLocation_UniLoc,
                    ::g_cameraEye.x, ::g_cameraEye.y, ::g_cameraEye.z, 1.0f);


    //        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
    //        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        matProjection = glm::perspective(
            0.6f,       // Field of view (in degress, more or less 180)
            ratio,
            0.1f,       // Near plane (make this as LARGE as possible)
            10000.0f);   // Far plane (make this as SMALL as possible)
                        // 6-8 digits of precision

//        glm::ortho(



        //    ____  _             _            __                           
        //   / ___|| |_ __ _ _ __| |_    ___  / _|  ___  ___ ___ _ __   ___ 
        //   \___ \| __/ _` | '__| __|  / _ \| |_  / __|/ __/ _ \ '_ \ / _ \
        //    ___) | || (_| | |  | |_  | (_) |  _| \__ \ (_|  __/ | | |  __/
        //   |____/ \__\__,_|_|   \__|  \___/|_|   |___/\___\___|_| |_|\___|
        //                                                                  
        // We draw everything in our "scene"
        // In other words, go throug the vec_pMeshObjects container
        //  and draw each one of the objects 
        for ( std::vector< cMeshObject* >::iterator itCurrentMesh = vec_pMeshObjects.begin(); 
              itCurrentMesh != vec_pMeshObjects.end();
              itCurrentMesh++ )
        {
            cMeshObject* pCurrentMeshObject = *itCurrentMesh;        // * is the iterator access thing

            if ( ! pCurrentMeshObject->bIsVisible )
            {
                // Skip the rest of the loop
                continue;
            }

    // 
            // Don't draw any "back facing" triangles
            glCullFace(GL_BACK);

            // Turn on depth buffer test at draw time
            glEnable(GL_DEPTH_TEST);

            // Make an "identity matrix"
     //       mat4x4_identity(m);
            matModel = glm::mat4x4(1.0f);  // identity matrix

            // Move the object 
            glm::mat4 matTranslation = glm::translate(glm::mat4(1.0f),
                                                      pCurrentMeshObject->position);

            // Rotate the object
            glm::mat4 matRoationZ = glm::rotate(glm::mat4(1.0f), 
                                                pCurrentMeshObject->rotation.z,                // Angle to rotate
                                                glm::vec3(0.0f, 0.0f, 1.0f));       // Axis to rotate around

            glm::mat4 matRoationY = glm::rotate(glm::mat4(1.0f), 
                                                pCurrentMeshObject->rotation.y,                // Angle to rotate
                                                glm::vec3(0.0f, 1.0f, 0.0f));       // Axis to rotate around

            glm::mat4 matRoationX = glm::rotate(glm::mat4(1.0f), 
                                                pCurrentMeshObject->rotation.x,                // Angle to rotate
                                                glm::vec3(1.0f, 0.0f, 0.0f));       // Axis to rotate around

            // Scale the object
            float uniformScale = pCurrentMeshObject->scale;
            glm::mat4 matScale = glm::scale(glm::mat4(1.0f),
                                            glm::vec3(uniformScale, uniformScale, uniformScale));

            // Applying all these transformations to the MODEL 
            // (or "world" matrix)
            matModel = matModel * matTranslation;

            matModel = matModel * matRoationX;
            matModel = matModel * matRoationY;
            matModel = matModel * matRoationZ;

            matModel = matModel * matScale;

//            matModel = 
//                 matModel
//               * matTranslation
//               * matRoationX
//               * matRoationY
//               * matRoationZ
//               * matScale;


    //        mat4x4_mul(mvp, p, m);
//            mvp = matProjection * matView * matModel;
//            glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

            // uniform mat4 mModel;
            // uniform mat4 mView;
            // uniform mat4 mProjection;
            //GLint mModel_location = glGetUniformLocation(shaderID, "mModel");       // program
            //GLint mView_location = glGetUniformLocation(shaderID, "mView");       // program
            //GLint mProjection_location = glGetUniformLocation(shaderID, "mProjection");       // program
            glUniformMatrix4fv(mModel_location, 1, GL_FALSE, glm::value_ptr(matModel));
            glUniformMatrix4fv(mView_location, 1, GL_FALSE, glm::value_ptr(matView));
            glUniformMatrix4fv(mProjection_location, 1, GL_FALSE, glm::value_ptr(matProjection));
            
            // Inverse transpose of a 4x4 matrix removes the right column and lower row
            // Leaving only the rotation (the upper left 3x3 matrix values)
            glm::mat4 mModelInverseTransform = glm::inverse(glm::transpose(matModel));
            glUniformMatrix4fv(mModelInverseTransform_location, 1, GL_FALSE, glm::value_ptr(mModelInverseTransform));

//            glPointSize(15.0f);

            // Wireframe
            if ( pCurrentMeshObject->isWireframe )
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // GL_POINT, GL_LINE, GL_FILL
            }
            else 
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      
            }


            // Setting the colour in the shader
            // uniform vec4 RGBA_Colour;

            GLint RGBA_Colour_ULocID = glGetUniformLocation(shaderID, "RGBA_Colour");

            glUniform4f(RGBA_Colour_ULocID,
                        pCurrentMeshObject->RGBA_colour.r,
                        pCurrentMeshObject->RGBA_colour.g,
                        pCurrentMeshObject->RGBA_colour.b,
                        pCurrentMeshObject->RGBA_colour.w);


            GLint bUseRGBA_Colour_ULocID = glGetUniformLocation(shaderID, "bUseRGBA_Colour");

            if ( pCurrentMeshObject->bUse_RGBA_colour )
            {
                glUniform1f(bUseRGBA_Colour_ULocID, (GLfloat)GL_TRUE );
            }
            else
            {
                glUniform1f(bUseRGBA_Colour_ULocID, (GLfloat)GL_FALSE);
            }

            //uniform bool bDoNotLight;	
            GLint bDoNotLight_Colour_ULocID = glGetUniformLocation(shaderID, "bDoNotLight");

            if ( pCurrentMeshObject->bDoNotLight )
            {
                glUniform1f(bDoNotLight_Colour_ULocID, (GLfloat)GL_TRUE );
            }
            else
            {
                glUniform1f(bDoNotLight_Colour_ULocID, (GLfloat)GL_FALSE);
            }


            // Choose the VAO that has the model we want to draw...
            sModelDrawInfo drawingInformation;
            if ( pVAOManager->FindDrawInfoByModelName(pCurrentMeshObject->meshName, drawingInformation) )
            {
                glBindVertexArray(drawingInformation.VAO_ID);

                glDrawElements(GL_TRIANGLES, 
                               drawingInformation.numberOfIndices, 
                               GL_UNSIGNED_INT,
                               (void*) 0 );

        //        glDrawArrays(GL_TRIANGLES, 0, numVerticesToDraw);
        //        glDrawArrays(GL_TRIANGLES, 0, thePlyInfo.numberOfvertices);
        //        glDrawArrays(GL_TRIANGLES, 0, 3);

                glBindVertexArray(0);

            }
            else
            {
                // Didn't find that model
                std::cout << "Error: didn't find model to draw." << std::endl;

            }//if ( pVAOManager...

        }//for ( unsigned int index
        //    _____           _          __                           
        //   | ____|_ __   __| |   ___  / _|  ___  ___ ___ _ __   ___ 
        //   |  _| | '_ \ / _` |  / _ \| |_  / __|/ __/ _ \ '_ \ / _ \
        //   | |___| | | | (_| | | (_) |  _| \__ \ (_|  __/ | | |  __/
        //   |_____|_| |_|\__,_|  \___/|_|   |___/\___\___|_| |_|\___|
        //                                                            


        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // Set the window title
        //glfwSetWindowTitle(window, "Hey");

        std::stringstream ssTitle;
        ssTitle << "Camera (x,y,z): "
            << ::g_cameraEye.x << ", "
            << ::g_cameraEye.y << ", "
            << ::g_cameraEye.z
            << "  Light #0 (xyz): "
            << ::g_pTheLightManager->vecTheLights[0].position.x << ", "
            << ::g_pTheLightManager->vecTheLights[0].position.y << ", "
            << ::g_pTheLightManager->vecTheLights[0].position.z
            << " linear: " << ::g_pTheLightManager->vecTheLights[0].atten.y
            << " quad: " << ::g_pTheLightManager->vecTheLights[0].atten.z;

        std::string theText = ssTitle.str();

        glfwSetWindowTitle(window, ssTitle.str().c_str() );
        // Or this:
        //std::string theText = ssTitle.str();
        //glfwSetWindowTitle(window, ssTitle.str().c_str() );

    }

    // Get rid of stuff
    delete pTheShaderManager;
    delete ::g_pTheLightManager;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}


void DrawConcentricDebugLightObjects(void)
{
    extern bool bEnableDebugLightingObjects;

    if ( ! bEnableDebugLightingObjects )
    {
        pDebugSphere_1->bIsVisible = false;
        pDebugSphere_2->bIsVisible = false;
        pDebugSphere_3->bIsVisible = false;
        pDebugSphere_4->bIsVisible = false;
        pDebugSphere_5->bIsVisible = false;
       return;
    }

    pDebugSphere_1->bIsVisible = true;
    pDebugSphere_2->bIsVisible = true;
    pDebugSphere_3->bIsVisible = true;
    pDebugSphere_4->bIsVisible = true;
    pDebugSphere_5->bIsVisible = true;

    cLightHelper theLightHelper;

            // Move the debug sphere to where the light #0 is
    pDebugSphere_1->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    pDebugSphere_2->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    pDebugSphere_3->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    pDebugSphere_4->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    pDebugSphere_5->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);

    {
        // Draw a bunch of concentric spheres at various "brightnesses" 
        float distance75percent = theLightHelper.calcApproxDistFromAtten(
            0.75f,  // 75%
            0.001f,
            100000.0f,
            ::g_pTheLightManager->vecTheLights[0].atten.x,
            ::g_pTheLightManager->vecTheLights[0].atten.y,
            ::g_pTheLightManager->vecTheLights[0].atten.z);

        pDebugSphere_2->scale = distance75percent;
        pDebugSphere_2->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    }

    {
        // Draw a bunch of concentric spheres at various "brightnesses" 
        float distance50percent = theLightHelper.calcApproxDistFromAtten(
            0.50f,  // 75%
            0.001f,
            100000.0f,
            ::g_pTheLightManager->vecTheLights[0].atten.x,
            ::g_pTheLightManager->vecTheLights[0].atten.y,
            ::g_pTheLightManager->vecTheLights[0].atten.z);

        pDebugSphere_3->scale = distance50percent;
        pDebugSphere_3->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    }

    {
        // Draw a bunch of concentric spheres at various "brightnesses" 
        float distance25percent = theLightHelper.calcApproxDistFromAtten(
            0.25f,  // 75%
            0.001f,
            100000.0f,
            ::g_pTheLightManager->vecTheLights[0].atten.x,
            ::g_pTheLightManager->vecTheLights[0].atten.y,
            ::g_pTheLightManager->vecTheLights[0].atten.z);

        pDebugSphere_4->scale = distance25percent;
        pDebugSphere_4->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    }

    {
        // Draw a bunch of concentric spheres at various "brightnesses" 
        float distance5percent = theLightHelper.calcApproxDistFromAtten(
            0.05f,  // 75%
            0.001f,
            100000.0f,
            ::g_pTheLightManager->vecTheLights[0].atten.x,
            ::g_pTheLightManager->vecTheLights[0].atten.y,
            ::g_pTheLightManager->vecTheLights[0].atten.z);

        pDebugSphere_5->scale = distance5percent;
        pDebugSphere_5->position = glm::vec3(::g_pTheLightManager->vecTheLights[0].position);
    }
    return;
}