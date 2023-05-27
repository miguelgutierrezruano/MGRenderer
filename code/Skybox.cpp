
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glad\glad.h>
#include <iostream>

#include "other/stb_image.h"
#include "Skybox.h"

namespace mg
{
	float Skybox::skyboxVertices[] =
	{
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	Skybox::Skybox() :
		vbo(skyboxVertices, sizeof(float) * 3 * 6 * 6)
	{
		facePaths =
		{
			"../resources/textures/sunset/left.png",
			"../resources/textures/sunset/right.png",
			"../resources/textures/sunset/top.png",
			"../resources/textures/sunset/bottom.png",
			"../resources/textures/sunset/front.png",
			"../resources/textures/sunset/back.png"
		};

		id = loadCubemap();

		VertexBufferLayout vbLayout;
		vbLayout.push<float>(3);

		vao.addBuffer(vbo, vbLayout);
	}

	Skybox::~Skybox()
	{
		glDeleteTextures(1, &id);
	}

	void Skybox::render(std::shared_ptr<Shader> shader)
	{
		glDepthMask(GL_FALSE);
		shader.get()->bind();
		vao.bind();

		glBindTexture(GL_TEXTURE_CUBE_MAP, id);

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
	}

	unsigned int Skybox::loadCubemap()
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		int width;
		int height;
		int nrChannels;

		unsigned char* data;

		for (unsigned int i = 0; i < facePaths.size(); i++)
		{
			data = stbi_load(facePaths[i].c_str(), &width, &height, &nrChannels, 0);

			if (data)
			{
				// Load each image of the cubemap
				glTexImage2D
				(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
					0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
				);

				std::cout << "Loaded texture: " << facePaths[i] << std::endl;
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap tex failed to load at path: " << facePaths[i] << std::endl;
				stbi_image_free(data);
			}			
		}

		return textureID;
	}
}