
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <memory>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Transform.h"

using namespace std;

namespace mg
{
	class Model;

	struct Vertex
	{
		vec4 position;
		vec3 color;
	};

	// Struct Texture

	class Mesh
	{

	private:

		Model* owner;

		VertexArray  vao;
		VertexBuffer vbo;
		IndexBuffer  ibo;

	public:

		Mesh(Model* meshModel, vector<Vertex> meshVertices, vector<unsigned int> meshIndices);

	public:

		void render(shared_ptr< Shader > shader);
	};
}
