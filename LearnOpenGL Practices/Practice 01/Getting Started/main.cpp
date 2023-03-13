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

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int wWidth = 800;
const unsigned int wHeight = 800;

int main(int argc, const char * argv[]) {
    
    
    glfwInit(); // glfw initialization
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // configure glfw version as 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // add minor version num, the version became 3.3 now
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //  set profile mode as Core-Profile mode
    
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    // Mac OS X needed maybe it has to deal with dependencies or sth
    
    GLFWwindow* window = glfwCreateWindow(wWidth, wHeight, "LearnOpenGL", NULL, NULL);
    
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
    
    
    float vertices[] =
    {
        //    coordinates     /        colors        /     texture mapping
        -0.5f,  0.0f,   0.5f,   0.83f,   0.70f,   0.44f,   0.0f,   0.0f,
        -0.5f,  0.0f,   -0.5f,  0.83f,   0.70f,   0.44f,   5.0f,   1.0f,
        0.5f,   0.0f,   -0.5f,  0.83f,   0.70f,   0.44f,   0.0f,   0.0f,
        0.5f,   0.0f,   0.5f,   0.83f,   0.70f,   0.44f,   5.0f,   0.0f,
        0.0f,   0.8f,   0.0f,   0.92f,   0.86f,   0.76f,   2.5f,   5.0f
    };
    
    GLuint indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };
    
    //rendering commands
    // specify the color of the background

    glViewport(0, 0, 2*wWidth, 2*wHeight);
    
    Shader ShaderProgram("default.vert", "default.frag");
    
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    //binding vbo1 and vao1 of data layout 0

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    //binding vbo1 and vao1 of data layout 1
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 3, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();
    
    //GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");
        
    Texture FELIX("filex.jpeg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
    FELIX.TexUnit(ShaderProgram, "tex0", 0);
/*    float rotation = 0 ;
    double prevTime = glfwGetTime();*/
    glEnable(GL_DEPTH_TEST);
    
    
    Camera camera(wWidth, wHeight, glm::vec3(0.0f, 0.0f, 2.0f));

    //main while loop
    while(!glfwWindowShouldClose(window))
    {
        // input processing
        processInput(window);
        camera.Inputs(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        
        /*double crntTime = glfwGetTime();
        if (crntTime - prevTime >= 1/60)
        {
            rotation += 0.5f;
            prevTime = crntTime;
        }*/

        ShaderProgram.Activate();
        camera.Matrix(45, 0.1f, 100.f, ShaderProgram, "camMatrix");
        
        /*
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::mat4(1.0f);

        // beform Assigning uniform value, don't forget to activate the shader program
        int modelLoc = glad_glGetUniformLocation(ShaderProgram.ID, "model");
        int viewLoc = glad_glGetUniformLocation(ShaderProgram.ID, "view");
        int projLoc = glad_glGetUniformLocation(ShaderProgram.ID, "proj");
        
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        proj = glm::perspective(glm::radians(45.0f), float(wWidth/wHeight), 0.1f, 100.f);
        
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
         
        //should use uniform function after activating the Shader Program
        glUniform1f(uniID, 0.5f);
        
         */
        
        FELIX.Bind();
        VAO1.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
    VAO1.Delete();
    VBO1.Delete();    
    EBO1.Delete();
    FELIX.Delete();
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
