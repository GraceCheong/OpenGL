//
//  main.cpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/05.
//

#include <iostream>
#include "glad.h"
// be sure to include glad before glfw
// be sure to include GLAD before other header files that require OpenGL
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "ShaderClass.hpp"
#include "VBO.hpp"
#include "VAO.hpp"
#include "EBO.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Model.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int initOGL();

const unsigned int wWidth = 800;
const unsigned int wHeight = 800;

GLFWwindow* window;


int main(int argc, const char * argv[]) {
    
    if(initOGL() == -1) return -1;
    
    //rendering commands
    // specify the color of the background

    glViewport(0, 0, 2*wWidth, 2*wHeight);
    
    /*Texture texs[] =
    {
        Texture("Textures/planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
        Texture("Textures/planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };
    */
    Shader ShaderProgram("default.vert", "default.frag");
    
    /*
     std::vector <Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector <GLuint> ind(indices, indices + sizeof(indices)/sizeof(GLuint));
    std::vector <Texture> tex(texs, texs + sizeof(texs) / sizeof(Texture));*/
    
    //Mesh floor(verts, ind, tex);
    //GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");
    // light shader 읽어오기
    //Shader lightShader("light.vert", "light.frag");
    // light VAO 선언
    /*
    std::vector <Vertex> lightVert(lightVertices, lightVertices + sizeof(lightVertices)/sizeof(Vertex));
    std::vector <GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices)/sizeof(GLuint));
    Mesh lights(lightVert, lightInd, tex);
     */
    
    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    
    /*
     glm::vec3 PyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 PyramidModel = glm::mat4(1.0f);
    PyramidModel = glm::translate(PyramidModel, PyramidPos);
    */
    
    /*
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    */
    
    ShaderProgram.Activate();
    //glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(PyramidModel));
    glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    
    /*    float rotation = 0 ;
    double prevTime = glfwGetTime();*/
    glEnable(GL_DEPTH_TEST);
    
    Camera camera(wWidth, wHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    Model model("models/sword/scene.gltf");
    
    //main while loop
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // input processing
        processInput(window);
        camera.Inputs(window);
        camera.updateMatrix(45.0f, 0.1f, 100.0f);
        
        model.Draw(ShaderProgram, camera);

        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ShaderProgram.Delete();
    
    glfwTerminate(); //terminate glfw cause glfwShouldClose is occurred
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    else if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int initOGL()
{
    glfwInit(); // glfw initialization
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // configure glfw version as 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // add minor version num, the version became 3.3 now
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //  set profile mode as Core-Profile mode
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Mac OS X needed maybe it has to deal with dependencies or sth
    
    window = glfwCreateWindow(wWidth, wHeight, "LearnOpenGL", NULL, NULL);
    
    /*
     create window with following information as parameters
     
     GLFWwindow * glfwCreateWindow(
     int            width,
     int            height,
     const char *   title,
     GLFWmonitor *  monitor,
     GLFWwindow *   share
     )
     
     We can ignore the last 2 parameters in this example
     */
    
    if (window == NULL) // if window not created, terminate the program
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate(); // terminate the glfw
        return -1; // terminate program
    }
    glfwMakeContextCurrent(window); // thread context managing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // framebuffer_size_callback function is set as FramebufferSizeCallBack (glfw provided)

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // if glad not loaded? other functionallities quit the program
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1; // exit
    }
    
    return 0;
}
