
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
		: cubeXRotation(0),
		cubeYRotation(0),
		mouseLastPosition(0, 0),
		mainCamera(45, 0.1f, 50.f)
	{
		mainCamera.transform.set_position({ 0, 0, -8 });

		// Get from camera get projection
		glm::mat4 projection = mainCamera.get_projection_matrix((float)width / (float)height);

		shader = make_shared<Shader>("../code/shaders/Basic.shader");

		shader.get()->bind();
		shader.get()->setUniformMat4f("projection", projection);

		cube = make_shared<Mesh>();
		childCube = make_shared<Mesh>();
		grandchildCube = make_shared<Mesh>();

		childCube.get()->transform.set_parent(&cube.get()->transform);
		childCube.get()->transform.set_position({ 2, 0, 0 });
		childCube.get()->transform.set_scale({ .5f, .5f, .5f });

		grandchildCube.get()->transform.set_parent(&childCube.get()->transform);
		grandchildCube.get()->transform.set_position({ 0, 2, 0 });
		grandchildCube.get()->transform.set_scale({ .5f, .5f, .5f });

		Model model("../resources/models/japan.fbx");
	}

	void Renderer::update(float delta)
	{
		update_camera(delta);

		glm::mat4 view = mainCamera.get_view_matrix();
		shader.get()->bind();
		shader.get()->setUniformMat4f("view", view);

		cubeXRotation += 0.05f;
		cubeYRotation += 0.2f;
		cube.get()->transform.set_rotation(vec3(cubeXRotation, cubeYRotation, 0));
	}

	void Renderer::render()
	{
		cube.get()->render(shader);
		childCube.get()->render(shader);
		grandchildCube.get()->render(shader);
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
