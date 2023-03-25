//
//  Texture.cpp
//  OpenGLPractice
//
//  Created by 정다은 on 2023/03/12.
//

#include "Texture.hpp"

Texture::Texture(const char * image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType)
{
    // texture
    type = texType;
    int widthImg, heightImg, numColch;
    
    
    stbi_set_flip_vertically_on_load(true);
    unsigned char * bytes = stbi_load("felix.jpeg", &widthImg, &heightImg, &numColch, 0);
    
    
    glGenTextures(1, &ID);
    glActiveTexture(slot);
    
    glBindTexture(type, ID);
    
    
    // configuring texturing patterns
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    float flatcolor[] = {0.05f, 0.05f, 0.05f, 0.3f};
    glTexParameterfv(type, GL_TEXTURE_BORDER_COLOR, flatcolor);
 
    glTexImage2D(type, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(type);
    
    stbi_image_free(bytes);
    glBindTexture(type, 0);
    
}
void Texture::TexUnit(Shader& shader, const char* uniform, GLuint unit)
{
    GLuint tex0Uni = glGetUniformLocation(shader.ID, uniform);
    shader.Activate();
    glUniform1i(tex0Uni, 0);
}

void Texture::Bind()
{
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
