
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <string>
#include <vector>
#include <memory>

#include <VertexArray.h>
#include <VertexBuffer.h>

#include "Shader.h"

namespace mg
{
	class Skybox
	{  

	private:

		// Here to not complicate renderer class
		std::vector< std::string > facePaths;
		static float skyboxVertices[];

		unsigned int id;

		VertexArray  vao;
		VertexBuffer vbo;

	public:

		Skybox();
	   ~Skybox();

	public:

		void render(std::shared_ptr<Shader> shader);

	private:

		unsigned int loadCubemap();
	};
}
