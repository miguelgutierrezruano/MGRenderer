
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "OpenGLDebugger.h"
#include "Model.h"

#include <random>

namespace mg
{
	Model::Model(const char* model_path)
	{
		loadModel(model_path);
	}

	void Model::render(shared_ptr<Shader> shader)
	{
		for (auto& mesh : model_meshes)
		{
			GLClearError();
			mesh.get()->render(shader);
			GLLogCall();
		}
	}

	void Model::loadModel(const char* model_path)
	{
		// Create assimp importer
		Assimp::Importer importer;

		// Read 3D file scene
		auto scene = importer.ReadFile
		(
			model_path,
			aiProcess_Triangulate |
			aiProcess_MakeLeftHanded |
			aiProcess_FlipUVs
		);

		if (scene && scene->mNumMeshes > 0)
		{
			processNode(scene->mRootNode, scene, scene->mRootNode->mTransformation);
		}
	}

	void Model::processNode(aiNode* node, const aiScene* scene, aiMatrix4x4 parentTransform)
	{
		aiMatrix4x4 nodeTransform = parentTransform * node->mTransformation;

		// Process all node meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			processMesh(mesh, scene, nodeTransform);
		}

		// Recursive for children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, nodeTransform);
		}
	}

	void Model::processMesh(aiMesh* mesh, const aiScene* scene, aiMatrix4x4 nodeTransform)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<Texture> textures;

		// Get color of mesh
		aiColor4D diffuse_color;

		// Get material of mesh
		auto material = scene->mMaterials[mesh->mMaterialIndex];
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse_color);

		mat4 transformation = aiToGlm(nodeTransform);

		// Process vertices
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;

			// Position
			auto& aiVertex = mesh->mVertices[i];
			vertex.position = vec3(transformation * vec4(aiVertex.x, aiVertex.y, aiVertex.z, 1));

			// Normal
			auto& aiNormal = mesh->mNormals[i];
			vertex.normal = vec3(transformation * vec4(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z, 0));

			// Texture coordinates
			/*if (mesh->mTextureCoords[0])
			{
				vec2 textureCoordinates;
				textureCoordinates.x = mesh->mTextureCoords[0][i].x;
				textureCoordinates.y = mesh->mTextureCoords[0][i].y;
				vertex.texCoords = textureCoordinates;
			}
			else*/
				vertex.texCoords = vec2(0.5, 0.5);

			vertices.push_back(vertex);
		}

		// Process indices
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			assert(face.mNumIndices == 3);

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		shared_ptr< Mesh > mgMesh = make_shared<Mesh>(this, vertices, indices, textures);
		model_meshes.push_back(mgMesh);
	}

	mat4 Model::aiToGlm(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		to[0][0] = from.a1; to[0][1] = from.b1; to[0][2] = from.c1; to[0][3] = from.d1;
		to[1][0] = from.a2; to[1][1] = from.b2; to[1][2] = from.c2; to[1][3] = from.d2;
		to[2][0] = from.a3; to[2][1] = from.b3; to[2][2] = from.c3; to[2][3] = from.d3;
		to[3][0] = from.a4; to[3][1] = from.b4; to[3][2] = from.c4; to[3][3] = from.d4;
		return to;
	}
}