//
//  VBO.h
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include "glad.h"
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 texUV;
};

class VBO
{
public:
    GLuint ID;
    VBO(std::vector<Vertex>& vertices);
    
    void Bind();
    void UnBind();
    void Delete();
};


#endif /* VBO_CLASS_H */
