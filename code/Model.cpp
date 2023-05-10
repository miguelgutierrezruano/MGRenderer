
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
		// If node has meshes copy them
		if (node->mNumMeshes > 0)
		{
			copyMeshes(node, scene, parentTransform);
		}

		// Copy nodes foreach child in node
		for (unsigned i = 0; i < node->mNumChildren; i++)
		{
			copyNodesRecursive(node->mChildren[i], scene, parentTransform * node->mTransformation);
		}
	}

	void Model::copyMeshes(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform)
	{

	}
}