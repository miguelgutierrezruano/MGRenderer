
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Renderer.h"

using namespace sf;

namespace mg
{
	Renderer::Renderer(unsigned int width, unsigned int height)
		: modelYRotation(0),
		mouseLastPosition(0, 0),
		mainCamera(45, 0.1f, 150.f)
	{
		mainCamera.transform.set_position({ 0, 8, -30 });

		// Get from camera get projection
		glm::mat4 projection = mainCamera.get_projection_matrix((float)width / (float)height);

		modelShader = make_shared<Shader>("../code/shaders/PhongColor.shader");

		modelShader.get()->bind();
		modelShader.get()->setUniformMat4f("projection", projection);
		modelShader.get()->setUniform3f("lightColor", light.get_color());

		basicShader = make_shared<Shader>("../code/shaders/Basic.shader");

		basicShader.get()->bind();
		basicShader.get()->setUniformMat4f("projection", projection);

		model = make_shared<Model>("../resources/models/japan.fbx");
		model.get()->transform.set_scale(vec3(0.01f, 0.01f, 0.01f));

		light.transform.set_position(vec3(0, 3, 0));
		light.transform.set_rotation(vec3(0, 45, 0));
		light.transform.set_scale(vec3(0.1, 0.1, 0.1));

		modelShader.get()->bind();
		modelShader.get()->setUniform3f("lightPos", light.transform.get_position());
	}

	void Renderer::update(float delta)
	{
		update_camera(delta);

		glm::mat4 view = mainCamera.get_view_matrix();
		modelShader.get()->bind();
		modelShader.get()->setUniformMat4f("view", view);
		modelShader.get()->setUniform3f("viewPos", mainCamera.transform.get_position());

		basicShader.get()->bind();
		basicShader.get()->setUniformMat4f("view", view);

		modelYRotation += 0.2f;
		model.get()->transform.set_rotation(vec3(0, modelYRotation, 0));
	}

	void Renderer::render()
	{
		model.get()->render(modelShader);
		light.render(basicShader);
	}

	void Renderer::update_camera(float delta)
	{
		vec2 currentMousePosition = vec2(Mouse::getPosition().x, Mouse::getPosition().y);
		vec2 positionDifference = currentMousePosition - mouseLastPosition;

		mouseLastPosition = currentMousePosition;

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			mainCamera.move_camera(positionDifference, delta);
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Middle))
		{
			mainCamera.move_camera(positionDifference, delta);
		}
		else if (Mouse::isButtonPressed(Mouse::Button::Right))
		{
			float xAxis = 0;
			float zAxis = 0;

			if (Keyboard::isKeyPressed(Keyboard::W))
				zAxis++;
			if (Keyboard::isKeyPressed(Keyboard::A))
				xAxis--;
			if (Keyboard::isKeyPressed(Keyboard::S))
				zAxis--;
			if (Keyboard::isKeyPressed(Keyboard::D))
				xAxis++;

			mainCamera.move_camera_x_axis(xAxis, delta);
			mainCamera.move_camera_z_axis(zAxis, delta);

			mainCamera.rotate_camera(positionDifference, delta);
		}
	}

	void Renderer::zoom_camera(sf::Event& event, float delta)
	{
		if (event.type == Event::MouseWheelScrolled)
		{
			float zAxis = 0;

			if (event.mouseWheelScroll.delta > 0)
				zAxis++;
			else
				zAxis--;

			mainCamera.move_camera_z_axis(zAxis * 5.f, delta);
		}
	}
}
