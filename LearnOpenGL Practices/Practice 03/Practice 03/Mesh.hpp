//
//  Mesh.hpp
//  Practice 03
//
//  Created by 정다은 on 2023/03/26.
//

#ifndef MESH_CLASS_HPP
#define MESH_CLASS_HPP

#include <string>
#include <vector>
#include <glm/glm.hpp>

#include "VAO.hpp"
#include "EBO.hpp"
#include "Camera.hpp"
#include "Texture.hpp"

// mesh = vertices(vbo, vao) + indicies(ebo) + shader(texture + camera)


class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;
    
    VAO VAO;
    
    Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, std::vector<Texture>& textures);
    
    void Draw(
              Shader& shader,
              Camera& camera,
              glm::mat4 matrix = glm::mat4(1.0f),
              glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
              glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
              glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
              );
    
};


#endif /* Mesh_hpp */
