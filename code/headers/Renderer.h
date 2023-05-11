
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <glad/glad.h>
#include <iostream>
#include <memory>
#include <SFML/Window.hpp>
#include <glm/glm.hpp>

#include "Model.h"
#include "Camera.h"
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
		Camera mainCamera;

		// Entity array
		// Light array

		// Convert to material
		shared_ptr < Shader > shader;

		// vector of shared_ptr models

		shared_ptr < Model > model;

		float cubeXRotation;
		float cubeYRotation;

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

