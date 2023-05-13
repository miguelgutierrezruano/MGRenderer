
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Mesh.h"
#include "Model.h"
#include "Light.h"
#include "Camera.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

namespace mg
{
	class Renderer
	{

	private:

		// Camera
		Camera mainCamera;

		// Convert to material
		shared_ptr < Shader > modelShader;
		shared_ptr < Shader > basicShader;

		// vector of shared_ptr models
		shared_ptr < Model > model;

		// Light vector
		Light light;

		Texture texture;

		float modelYRotation;

		glm::vec2 mouseLastPosition;

	public:

		Renderer(unsigned int width, unsigned int height);

	public:

		void update_camera(float delta);
		void zoom_camera(sf::Event& event, float delta);

		void update(float delta);
		void render();
	};
}

