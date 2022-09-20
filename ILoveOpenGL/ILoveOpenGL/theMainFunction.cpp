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


struct sVertex_XY_RGB
{
    float x, y, z;             // 0 floats from the start
    float r, g, b;          // 2 floats from the start
                     // Each vertex is 5 floats in size
};

//sVertex_XY_RGB vertices[] =
//{
//        { -0.6f, -0.4f, 0.0, 1.0f, 0.0f, 0.0f },
//        {  0.6f, -0.4f, 0.0, 0.0f, 1.0f, 0.0f },
//        {  0.0f,  0.6f, 0.0, 0.0f, 0.0f, 1.0f },
//
//        { (-0.6f + 1.0f), -0.4f, 0.0,  0.0f, 1.0f, 0.0f },
//        {  (0.6f + 1.0f), -0.4f, 0.0,  0.0f, 0.0f, 1.0f },
//        {  (0.0f + 1.0f),  0.6f, 0.0,  1.0f, 0.0f, 0.0f }
//};

const unsigned int NUMBER_OF_VERTICES = 100;

sVertex_XY_RGB* vertices = new sVertex_XY_RGB[NUMBER_OF_VERTICES];

glm::vec3 g_cameraEye = glm::vec3(0.0, 0.0, -200.0f);
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


void LoadTheFile()
{
    std::ifstream theFile("assets/models/bun_zipper_xyz.ply");
    if ( ! theFile.is_open() )
    {
        std::cout << "Didn't open it!" << std::endl;
        return;
    }

    std::string theNextToken;
    while ( theFile >> theNextToken )
    {
        // Do something with the data
        std::cout << theNextToken << std::endl;
    }

    theFile.close();

    return;
}


int main(void)
{
    LoadTheFile();

    // Create a bunch of random triangles
    for ( unsigned int index = 0; index != NUMBER_OF_VERTICES; index++ )
    {
        vertices[index].x = RandomFloat(-50.0f, 50.0f);
        vertices[index].y = RandomFloat(-50.0f, 50.0f);
        vertices[index].z = RandomFloat(-50.0f, 50.0f);

        vertices[index].r = RandomFloat(0.0f, 1.0f);
        vertices[index].g = RandomFloat(0.0f, 1.0f);
        vertices[index].b = RandomFloat(0.0f, 1.0f);
    }

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


    // Defining the 3D model that we are going to draw. 
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    unsigned int vertexBufferSizeInBytes = sizeof(vertices) * NUMBER_OF_VERTICES;
    glBufferData(GL_ARRAY_BUFFER, 
                 vertexBufferSizeInBytes, 
                 vertices,              // (void*)
                 GL_STATIC_DRAW);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

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

    // Vertex layout
    vpos_location = glGetAttribLocation(shaderID, "vPos");   // Vertex Position
    vcol_location = glGetAttribLocation(shaderID, "vCol");

    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(sVertex_XY_RGB),   //  sizeof(vertices[0]),
                          (void*) offsetof(sVertex_XY_RGB, x));      //0);

    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 
                          3, 
                          GL_FLOAT, 
                          GL_FALSE,
                          sizeof(sVertex_XY_RGB),               //  sizeof(vertices[0]),
                          (void*) offsetof(sVertex_XY_RGB, r)); //  (sizeof(float) * 3));


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
        glClear(GL_COLOR_BUFFER_BIT);

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
        glDrawArrays(GL_TRIANGLES, 0, NUMBER_OF_VERTICES);
//        glDrawArrays(GL_TRIANGLES, 0, 3);

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
