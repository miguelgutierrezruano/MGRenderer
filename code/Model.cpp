
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "Model.h"

namespace mg
{
	Model::Model(const char* model_path)
	{
		loadModel(model_path);
	}

	void Model::loadModel(const char* model_path)
	{
		// Create assimp importer
		Assimp::Importer importer;

		// Read 3D file scene
		auto scene = importer.ReadFile
		(
			model_path,
			aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenNormals
		);

		if (scene && scene->mNumMeshes > 0)
		{
			aiNode* root = scene->mRootNode;

			// Iterate each aiNode to render model properly
			copyNodesRecursive(root, scene, root->mTransformation);
		}
	}

	void Model::copyNodesRecursive(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform)
	{

	}
}