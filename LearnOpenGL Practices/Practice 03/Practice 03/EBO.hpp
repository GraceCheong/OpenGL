//
//  EBO.hpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include "glad.h"
#include <vector>

class EBO
{
public:
    GLuint ID;
    EBO(std::vector<GLuint>& indices);
    
    void Bind();
    void UnBind();
    void Delete();
};


#endif /* EBO_hpp */
