//
//  VAO.hpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include "glad.h"
#include "VBO.hpp"

class VAO
{
public:
    GLuint ID;
    VAO();

    // due to Shader Source code has Edited, modify LinkVBO function
    // void LinkVBO(VBO VBO, GLuint layout);
    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    
    void Bind();
    void UnBind();
    void Delete();
};

#endif /* VAO_hpp */
