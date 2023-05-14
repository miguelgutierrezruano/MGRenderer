
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
	// Enum with light types

	// Light class is used as a cube right now
	class Light
	{

	public:

		Transform transform;

	protected:

		vec3 color;

	private:

		// Cube to represent light position
		static float vertices[];

		VertexArray  vao;
		VertexBuffer vbo;

	public:

		Light();

	public:

		const vec3 get_color() { return color; }

		void render(shared_ptr< Shader > shader);

	};
}