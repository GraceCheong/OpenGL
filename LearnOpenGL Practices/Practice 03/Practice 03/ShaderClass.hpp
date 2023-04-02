//
//  ShaderClass.h
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include "glad.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

std::string get_file_contents(const char* filename);

class Shader{
public:
    GLuint ID;
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Delete();
    void setVec3(const char* uniName, GLfloat x, GLfloat y, GLfloat z);
    
};

#endif /* ShaderClass_h */
