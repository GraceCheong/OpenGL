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
int initOGL();

const unsigned int wWidth = 800;
const unsigned int wHeight = 800;

GLFWwindow* window;

// Vertices coordinates
GLfloat vertices[] =
{ //     COORDINATES     /        COLORS             /    TexCoord    /       NORMALS     //
    -1.0f, 0.0f,  1.0f,        0.0f, 0.0f, 0.0f,        0.0f, 0.0f,        0.0f, 1.0f, 0.0f,
    -1.0f, 0.0f, -1.0f,        0.0f, 0.0f, 0.0f,        0.0f, 1.0f,        0.0f, 1.0f, 0.0f,
     1.0f, 0.0f, -1.0f,        0.0f, 0.0f, 0.0f,        1.0f, 1.0f,        0.0f, 1.0f, 0.0f,
     1.0f, 0.0f,  1.0f,        0.0f, 0.0f, 0.0f,        1.0f, 0.0f,        0.0f, 1.0f, 0.0f
};

// Indices for vertices order
GLuint indices[] =
{
    0, 1, 2,
    0, 2, 3
};

	
GLfloat lightVertices[] =
{ //     COORDINATES     //
    -0.1f, -0.1f,  0.1f,
    -0.1f, -0.1f, -0.1f,
     0.1f, -0.1f, -0.1f,
     0.1f, -0.1f,  0.1f,
    -0.1f,  0.1f,  0.1f,
    -0.1f,  0.1f, -0.1f,
     0.1f,  0.1f, -0.1f,
     0.1f,  0.1f,  0.1f
};

GLuint lightindices[] =
{
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};

glm::vec4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);
glm::vec3 lightPosition(0.5f, 0.5f, 0.5f);


int main(int argc, const char * argv[]) {
    
    if(initOGL() == -1) return -1;
    
    //rendering commands
    // specify the color of the background

    glViewport(0, 0, 2*wWidth, 2*wHeight);
    
    Shader ShaderProgram("default.vert", "default.frag");
    
    VAO VAO1;
    VAO1.Bind();
    
    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));
    //binding vbo1 and vao1 of data layout 0

    VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    //binding vbo1 and vao1 of data layout 1
    VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    VAO1.LinkAttrib(VBO1, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    
    VAO1.UnBind();
    VBO1.UnBind();
    EBO1.UnBind();
    
    
    //GLuint uniID = glGetUniformLocation(ShaderProgram.ID, "scale");
    // light shader 읽어오기
    Shader lightShader("light.vert", "light.frag");
    // light VAO 선언
    
    VAO lightVAO;
    lightVAO.Bind();
    
    VBO lightVBO(lightVertices, sizeof(lightVertices));
    EBO lightEBO(lightindices, sizeof(lightindices));
    
    lightVAO.LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    
    lightVAO.UnBind();
    lightVBO.UnBind();
    lightEBO.UnBind();
    
    glm::vec3 lightPos = lightPosition;
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    
    glm::vec3 PyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 PyramidModel = glm::mat4(1.0f);
    PyramidModel = glm::translate(PyramidModel, PyramidPos);
    
    lightShader.Activate();
    glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
    glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    
    ShaderProgram.Activate();
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(PyramidModel));
    glUniform4f(glGetUniformLocation(ShaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(ShaderProgram.ID, "lightPos"), lightPosition.x, lightPosition.y, lightPosition.z);

    
    
    Texture planks("Textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    planks.texUnit(ShaderProgram, "tex0", 0);
    
    // add specular map
    
    Texture SpecularTex("Textures/planksSpec.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    SpecularTex.texUnit(ShaderProgram, "tex1", 1);
    
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

        
        camera.updateMatrix(45, 0.1f, 100.f);
        
        
        ShaderProgram.Activate();
        glUniform3f(glGetUniformLocation(ShaderProgram.ID,"camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
        camera.Matrix(ShaderProgram, "camMatrix");
        
        planks.Bind();
        SpecularTex.Bind();
        
        VAO1.Bind();
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);
        
        lightShader.Activate();
        camera.Matrix(lightShader, "camMatrix");
        lightVAO.Bind();
        
        glDrawElements(GL_TRIANGLES, sizeof(lightindices)/sizeof(int), GL_UNSIGNED_INT, 0);
        
        glfwSwapBuffers(window);

        glfwPollEvents();
    }
    
    VAO1.Delete();
    VBO1.Delete();    
    EBO1.Delete();
    planks.Delete();
    SpecularTex.Delete();
    lightVAO.Delete();
    lightVBO.Delete();
    lightEBO.Delete();
    ShaderProgram.Delete();
    lightShader.Delete();
    
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
