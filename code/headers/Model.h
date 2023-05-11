
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <vector>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

using std::shared_ptr;
using std::vector;

namespace mg
{
	class Model
	{

	public:

		Transform transform;

	private:

		vector< shared_ptr< Mesh > > model_meshes;

	public:

		Model(const char* model_path);

	public:

		void render(shared_ptr< Shader > shader);

	private:

		void loadModel(const char* model_path);
		void copyNodesRecursive(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform);
		void copyMeshes(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform);
	};
}
