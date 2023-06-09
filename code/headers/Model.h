
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <vector>
#include <memory>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

using std::shared_ptr;
using std::vector;

namespace mg
{
	class Model
	{

	public:

		Transform transform;

	private:

		vector< shared_ptr< Texture > > loaded_textures;
		vector< shared_ptr<    Mesh > > model_meshes;

	public:

		Model(const char* model_path);

	public:

		void render(shared_ptr< Shader > shader);

	private:

		void loadModel(const char* model_path);
		void processNode(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform);
		void processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 nodeTransform);

		vector< shared_ptr< Texture > > loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		mat4 aiToGlm(const aiMatrix4x4& from);
	};
}
