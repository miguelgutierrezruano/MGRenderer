
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <memory>

#include "Transform.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

using std::shared_ptr;

namespace mg
{
	class Light
	{

	public:

		Transform transform;

		// Cube to represent light position
		static float vertices[];

	private:

		vec3 color;

		VertexArray  vao;
		VertexBuffer vbo;

	public:

		Light();

	public:

		void render(shared_ptr< Shader > shader);

	};
}