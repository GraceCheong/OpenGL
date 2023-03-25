//
//  Camera.hpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/13.
//

#ifndef CAMERA_CLASS_HPP
#define CAMERA_CLASS_HPP

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "ShaderClass.hpp"

class Camera
{
public:
    glm::vec3 Position;
    glm::vec3 Orientation = glm::vec3(0.f, 0.f, -1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 camMatrix = glm::mat4(1.0f);
    
    int width;
    int height;
    
    float speed = 0.1f;
    float sensitivity = 100.f;
    
    bool firstClick = true;
    
    Camera(int width, int height, glm::vec3 position);
    
    void Inputs(GLFWwindow* window);
    
    // updates and exports the cameramatrix to the vertex shader
    void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
    void Matrix(Shader& shader, const char* uniform);
};

#endif /* Camera_hpp */
