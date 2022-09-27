
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

#include "cShaderManager.h"

#include "cVAOManager/cVAOManager.h"


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

glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, -4.0f);
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

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, 
                         int key, int scancode, 
                         int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    // Move the camera
    // AWSD   AD - left and right
    //        WS - forward and back
    const float CAMERA_MOVE_SPEED = 0.1f;
    if (key == GLFW_KEY_A )     // Left
    {
        ::g_cameraEye.x -= CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_D )     // Right
    {
        ::g_cameraEye.x += CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_W )     // Forward
    {
        ::g_cameraEye.z += CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_S )     // Backwards
    {
        ::g_cameraEye.z -= CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_Q )     // Down
    {
        ::g_cameraEye.y -= CAMERA_MOVE_SPEED;
    }
    if (key == GLFW_KEY_E )     // Up
    {
        ::g_cameraEye.y += CAMERA_MOVE_SPEED;
    }

    if ( key == GLFW_KEY_1 )
    {
        ::g_cameraEye = glm::vec3(-5.5f, -3.4f, 15.0f); 
    }

}
// From here: https://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats/5289624

float RandomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}



bool LoadTheFile(std::string filename, sModelDrawInfo &modelDrawInfo)
{
    struct sVertex_XYZ_N_RGBA_UV
    {
        float x, y, z;
        float nx, ny, nz;
        //uchar red, green, blue, alpha;
        float red, green, blue, alpha;
        float texture_u, texture_v;
    };

    struct sTrianglePLY
    {
        // The 3 vertex index values from the ply file
        unsigned int vertexIndices[3];
    };

    // Array we will load into
   sVertex_XYZ_N_RGBA_UV* pTheModelArray = NULL;   // NULL, 0, nullptr
   sTrianglePLY* pTheModelTriangleArray = NULL;
//    unsigned int numberOfvertices = 0;
//    unsigned int numberOfTriangles = 0;

    // Start loading the file

    std::ifstream theFile(filename);
    if ( ! theFile.is_open() )
    {
        std::cout << "Didn't open it!" << std::endl;
        return false;
    }

    // Read an entire line
    char buffer[10000];
    theFile.getline(buffer, 10000);
 
    std::string theNextToken;

    // Scan for the word "vertex"
    while ( theFile >> theNextToken )
    {
        if ( theNextToken == "vertex" )
        {
            break;
        }
    }
    // 
    theFile >> modelDrawInfo.numberOfVertices;

    // Scan for the word "face"
    while (theFile >> theNextToken)
    {
        if (theNextToken == "face")
        {
            break;
        }
    }
    // 
    theFile >> modelDrawInfo.numberOfTriangles;

    // Scan for the word "end_header"
    while (theFile >> theNextToken)
    {
        if (theNextToken == "end_header")
        {
            break;
        }
    }

    // Now we load the vertices
    // -0.036872 0.127727 0.00440925 0.2438786 0.9638011 -0.1077533 127 127 127 255 0.337485 0.8899501

    pTheModelArray = new sVertex_XYZ_N_RGBA_UV[modelDrawInfo.numberOfVertices];

    std::cout << "Loading";
    for ( unsigned int count = 0; count != modelDrawInfo.numberOfVertices; count++ )
    {
        theFile >> pTheModelArray[count].x;
        theFile >> pTheModelArray[count].y;
        theFile >> pTheModelArray[count].z;

        theFile >> pTheModelArray[count].nx;
        theFile >> pTheModelArray[count].ny;
        theFile >> pTheModelArray[count].nz;

        theFile >> pTheModelArray[count].red;
        theFile >> pTheModelArray[count].green;
        theFile >> pTheModelArray[count].blue;
        theFile >> pTheModelArray[count].alpha;

        theFile >> pTheModelArray[count].texture_u;
        theFile >> pTheModelArray[count].texture_v;

        if ( count % 10000 == 0 )
        {
            std::cout << ".";
        }
   }
    std::cout << "done" << std::endl;

    // Load the faces (or triangles)
    pTheModelTriangleArray = new sTrianglePLY[modelDrawInfo.numberOfTriangles];

    for ( unsigned int count = 0; count != modelDrawInfo.numberOfTriangles; count++ )
    {
        // 3 15393 15394 15395 
        unsigned int discard = 0;
        theFile >> discard;

        theFile >> pTheModelTriangleArray[count].vertexIndices[0];
        theFile >> pTheModelTriangleArray[count].vertexIndices[1];
        theFile >> pTheModelTriangleArray[count].vertexIndices[2];
    }

    theFile.close();

    modelDrawInfo.pVertices = new sVertex[modelDrawInfo.numberOfVertices];

    // Now copy the information from the PLY infomation to the model draw info structure
    for ( unsigned int index = 0; index != modelDrawInfo.numberOfVertices; index++ )
    {
        modelDrawInfo.pVertices[index].x = pTheModelArray[index].x;
        modelDrawInfo.pVertices[index].y = pTheModelArray[index].y;
        modelDrawInfo.pVertices[index].z = pTheModelArray[index].z;

        modelDrawInfo.pVertices[index].r = pTheModelArray[index].red;
        modelDrawInfo.pVertices[index].g = pTheModelArray[index].green;
        modelDrawInfo.pVertices[index].b = pTheModelArray[index].blue;
    }

    modelDrawInfo.numberOfIndices = modelDrawInfo.numberOfTriangles * 3;

    // This is the "index" (or element) buffer
    modelDrawInfo.pIndices = new unsigned int[modelDrawInfo.numberOfIndices];

    unsigned int vertex_element_index_index = 0;

    for ( unsigned int triangleIndex = 0; triangleIndex != modelDrawInfo.numberOfTriangles; triangleIndex++ )
    {
        modelDrawInfo.pIndices[vertex_element_index_index + 0] = pTheModelTriangleArray[triangleIndex].vertexIndices[0];
        modelDrawInfo.pIndices[vertex_element_index_index + 1] = pTheModelTriangleArray[triangleIndex].vertexIndices[1];
        modelDrawInfo.pIndices[vertex_element_index_index + 2] = pTheModelTriangleArray[triangleIndex].vertexIndices[2];

        // Each +1 of the triangle index moves the "vertex element index" by 3
        // (3 vertices per triangle)
        vertex_element_index_index += 3;
    }

    delete [] pTheModelArray;   
    delete [] pTheModelTriangleArray;


    return true;
}


int main(void)
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

    GLint mvp_location = 0;
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




    // Load the models
    cVAOManager* pVAOManager = new cVAOManager();


    sModelDrawInfo motoDrawInfo;

    std::string fileToLoad = "assets/models/MOTO/Blender (load from OBJ export) - only Moto_xyz_n_rgba_uv.ply";
    if (LoadTheFile(fileToLoad, motoDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("MOTO", motoDrawInfo, shaderID))
    {
        std::cout << "Loaded the MOTO model" << std::endl;
    }



    sModelDrawInfo bunnyDrawInfo;
    fileToLoad = "assets/models/bunny/reconstruction/bun_zipper_res2_xyz_n_rgba_uv.ply";
    if (LoadTheFile(fileToLoad, bunnyDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("Bunny", bunnyDrawInfo, shaderID))
    {
        std::cout << "Loaded the Bunny model" << std::endl;
    } 
    

    sModelDrawInfo BOPDrawInfo;
    fileToLoad = "assets/models/BirdOfPrey/BirdOfPrey_Exported.ply";
    if (LoadTheFile(fileToLoad, BOPDrawInfo))
    {
        std::cout << "Loaded the file OK" << std::endl;
    }
    if (pVAOManager->LoadModelIntoVAO("BirdOfPrey", BOPDrawInfo, shaderID))
    {
        std::cout << "Loaded the BirdOfPrey model" << std::endl;
    } 
    
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


    mvp_location = glGetUniformLocation(shaderID, "MVP");       // program


    while ( ! glfwWindowShouldClose(window) )
    {
        float ratio;
        int width, height;
//        mat4x4 m, p, mvp;
        glm::mat4x4 m, p, mvp;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);

        // Turn on depth buffer test at draw time
        glEnable(GL_DEPTH_TEST);

        // Don't draw any "back facing" triangles
        glCullFace(GL_BACK);


        // note the binary OR (not the usual boolean "or" comparison)
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glClear(GL_COLOR_BUFFER_BIT);

        // Make an "identity matrix"
 //       mat4x4_identity(m);
        m = glm::mat4x4(1.0f);  // identity matrix

//        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
//        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        p = glm::perspective(0.6f,
                             ratio,
                             0.1f,
                             1000.0f);

        glm::mat4x4 v = glm::mat4(1.0f);

        //glm::vec3 cameraEye = glm::vec3(0.0, 0.0, -4.0f);
        //glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 upVector = glm::vec3(0.0f, 1.0f, 0.0f);

        v = glm::lookAt(::g_cameraEye,
                        ::g_cameraTarget,
                        upVector);

//        mat4x4_mul(mvp, p, m);
        mvp = p * v * m; 


        //glUseProgram(program);

        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));

        glPointSize(15.0f);

        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // GL_POINT, GL_LINE


        // Choose the VAO that has the model we want to draw...
        sModelDrawInfo drawingInformation;
        if ( pVAOManager->FindDrawInfoByModelName("MOTO", drawingInformation) )
//        if ( pVAOManager->FindDrawInfoByModelName("Bunny", drawingInformation) )
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

        }//if ( pVAOManager...


        glfwSwapBuffers(window);
        glfwPollEvents();
        
        // Set the window title
        //glfwSetWindowTitle(window, "Hey");

        std::stringstream ssTitle;
        ssTitle << "Camera (x,y,z): "
            << ::g_cameraEye.x << ", "
            << ::g_cameraEye.y << ", "
            << ::g_cameraEye.z;

        std::string theText = ssTitle.str();

        glfwSetWindowTitle(window, ssTitle.str().c_str() );
        // Or this:
        //std::string theText = ssTitle.str();
        //glfwSetWindowTitle(window, ssTitle.str().c_str() );

    }

    // Get rid of stuff
    delete pTheShaderManager;

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}
