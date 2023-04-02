//
//  EBO.cpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#include "EBO.hpp"

EBO::EBO(std::vector<GLuint>& indices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

void EBO::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

}
void EBO::UnBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}
void EBO::Delete()
{
    glDeleteBuffers(1, &ID);
}
