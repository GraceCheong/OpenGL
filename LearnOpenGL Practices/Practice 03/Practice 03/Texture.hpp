//
//  Texture.hpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef Texture_CLASS_H
#define Texture_CLASS_H

#include "glad.h"
#include "stb_image.h"
#include "ShaderClass.hpp"

class Texture
{
public:
    GLuint ID;
    const char * type;
    GLuint unit;
    Texture(const char * image, const char * texType, GLenum slot);
    
    
    void texUnit(Shader& shader, const char* uniform, GLuint unit);
    void Bind();
    void UnBind();
    void Delete();
    
};


#endif /* Texture_hpp */
