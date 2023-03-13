//
//  VAO.cpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#include "VAO.hpp"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}

void VAO::LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.Bind();
    
    //glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);

    glEnableVertexAttribArray(layout);
    
    VBO.UnBind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::UnBind()
{
    glBindVertexArray(0);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);

}
