
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <memory>
#include <vector>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Transform.h"
#include "Texture.h"

using namespace std;

namespace mg
{
	class Model;

	struct Vertex
	{
		vec3 position;
		vec3 normal;
		vec2 texCoords;
	};

	class Mesh
	{

	private:

		Model* owner;

		vector< shared_ptr<Texture> > textures;

		VertexArray  vao;
		VertexBuffer vbo;
		IndexBuffer  ibo;

	public:

		Mesh(Model* meshModel, vector<Vertex> meshVertices, vector<unsigned int> meshIndices, vector<shared_ptr<Texture>> textures);

	public:

		void render(shared_ptr< Shader > shader);
	};
}
