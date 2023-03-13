//
//  VBO.h
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "glad.h"

class VBO
{
public:
    GLuint ID;
    VBO(GLfloat* vertices, GLsizeiptr size);
    
    void Bind();
    void UnBind();
    void Delete();
};


#endif /* VBO_CLASS_H */
