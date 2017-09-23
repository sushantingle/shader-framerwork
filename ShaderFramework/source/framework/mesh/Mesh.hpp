#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "glm\glm.hpp"
#include "glm\gtx\transform.hpp"
#include <string>
#include <vector>
#include "../framework/shader/Shader.hpp"
#include "assimp\scene.h"

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;  // we store the path of the texture to compare with other textures
};
class Mesh {
public:
	std::vector<Vertex>  m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture> m_textures;
	/*  Functions  */
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);

private:
	/*  Render data  */
	unsigned int VAO, VBO, EBO;
	/*  Functions    */
	void setupMesh();
	
};

#endif //__MESH_HPP__
