
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <memory>

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using std::shared_ptr;

namespace mg
{
	// For now this is a cube to test
	class Mesh
	{

	private:

		VertexArray  vao;
		VertexBuffer vbo;
		IndexBuffer  ibo;

		Shader* shader;

		static const GLfloat vertexAttributes[];
		static const GLuint indices[];

	public:

		Mesh(Shader* meshShader);

	public:

		void render();
	};
}
