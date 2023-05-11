
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "Model.h"

namespace mg
{
	Model::Model(const char* model_path)
	{
		vector<Vertex> vertices;

		Vertex v1;
		v1.position = vec3(-3, -3, 0);
		v1.color = (vec3(1, 0, 0));

		Vertex v2;
		v2.position = vec3(3, -3, 0);
		v2.color = (vec3(1, 0, 0));

		Vertex v3;
		v3.position = vec3(0, 3, 0);
		v3.color = (vec3(1, 0, 0));

		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);

		vector<unsigned int> indices;

		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		shared_ptr< Mesh > triangle = make_shared<Mesh>(this, vertices, indices);
		model_meshes.push_back(triangle);
	}

	void Model::render(shared_ptr<Shader> shader)
	{
		for (auto& mesh : model_meshes)
		{
			mesh.get()->render(shader);
		}
	}

	void Model::loadModel(const char* model_path)
	{
		//// Create assimp importer
		//Assimp::Importer importer;

		//// Read 3D file scene
		//auto scene = importer.ReadFile
		//(
		//	model_path,
		//	aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType | aiProcess_GenNormals
		//);

		//if (scene && scene->mNumMeshes > 0)
		//{
		//	aiNode* root = scene->mRootNode;

		//	// Iterate each aiNode to render model properly
		//	copyNodesRecursive(root, scene, root->mTransformation);
		//}
	}

	void Model::copyNodesRecursive(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform)
	{
		//// If node has meshes copy them
		//if (node->mNumMeshes > 0)
		//{
		//	copyMeshes(node, scene, parentTransform);
		//}

		//// Copy nodes foreach child in node
		//for (unsigned i = 0; i < node->mNumChildren; i++)
		//{
		//	copyNodesRecursive(node->mChildren[i], scene, parentTransform * node->mTransformation);
		//}
	}

	void Model::copyMeshes(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform)
	{

	}
}