#ifndef __MODEL_HPP__
#define __MODEL_HPP__

#include "../framework/shader/Shader.hpp"
#include <vector>
#include <string>
#include "assimp\Importer.hpp"
#include "assimp\scene.h"
#include "assimp\postprocess.h"
#include "Mesh.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model
{
public:
	std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.

	/*  Functions   */
	Model(char *path)
	{
		loadModel(path);
	}
	void Draw(Shader shader);
private:
	/*  Model Data  */
	std::vector<Mesh> meshes;
	std::string directory;
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
		std::string typeName);
};

#endif //__MODEL_HPP__
