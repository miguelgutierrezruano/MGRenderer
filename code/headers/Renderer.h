
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <glad/glad.h>
#include <iostream>
#include <memory>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"

using namespace std;

namespace mg
{
	class Renderer
	{

	private:

		// Camera
		// Entity array
		// Light array

		// Convert to material
		shared_ptr < Shader > shader;

		shared_ptr < Mesh > cube;
		shared_ptr < Mesh > childCube;

		float cubeXRotation;
		float cubeYRotation;

	public:

		Renderer(unsigned int width, unsigned int height);

	public:

		void update();
		void render();
	};
}

