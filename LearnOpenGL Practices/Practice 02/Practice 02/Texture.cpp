//
//  Texture.cpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#include "Texture.hpp"
#include <iostream>

Texture::Texture(const char * image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // texture
    type = texType;
    int widthImg, heightImg, numColch;
    
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char * bytes = stbi_load(image, &widthImg, &heightImg, &numColch, 0);
    if (!bytes)
    {
        std::cout << "failed to load the texture image." << std::endl;
    }
    
    glGenTextures(1, &ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(type, ID);
    
    
    // configuring texturing patterns
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    float flatcolor[] = {0.095f, 0.95f, 0.95f, 0.3f};
    glTexParameterfv(type, GL_TEXTURE_BORDER_COLOR, flatcolor);
 
    glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(type);
    
    stbi_image_free(bytes);
    glBindTexture(type, 0);
    
}
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex0Uni, unit);
}

void Texture::Bind()
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(type, ID);
}
void Texture::UnBind()
{
    glBindTexture(type, 0);
}
void Texture::Delete()
{
    glDeleteTextures(1, &ID);
}
