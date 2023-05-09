
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
	struct Vertex
	{
		vec3 position;
		vec3 color;
	};

	class Mesh
	{

	public:

		Transform transform;

	private:

		VertexArray  vao;
		VertexBuffer vbo;
		IndexBuffer  ibo;

		// TODO: Change for materials
		shared_ptr< Shader > shader;

		static const Vertex vertexAttributes[];
		static const GLuint indices[];

	public:

		Mesh(shared_ptr< Shader > meshShader);

	public:

		void render();
	};
}
