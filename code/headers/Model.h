
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace mg
{
	class Model
	{

	private:


	public:

		Model(const char* model_path);

	private:

		void loadModel(const char* model_path);
		void copyNodesRecursive(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform);
	};
}
