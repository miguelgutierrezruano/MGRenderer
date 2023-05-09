
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

namespace mg
{
	Renderer::Renderer(unsigned int width, unsigned int height)
		: cubeXRotation(0),
		cubeYRotation(0),
		mainCamera(45, 0.1f, 50.f)
	{
		mainCamera.transform.set_position({ 0, 0, -8 });

		// Get from camera transform
		glm::mat4 view = mainCamera.get_view_matrix();

		// Get from camera get projection
		glm::mat4 projection = mainCamera.get_projection_matrix((float)width / (float)height);

		shader = make_shared<Shader>("../code/shaders/Basic.shader");

		shader.get()->bind();
		shader.get()->setUniformMat4f("view", view);
		shader.get()->setUniformMat4f("projection", projection);

		cube = make_shared<Mesh>(shader);
		childCube = make_shared<Mesh>(shader);
		grandchildCube = make_shared<Mesh>(shader);

		childCube.get()->transform.set_parent(&cube.get()->transform);
		childCube.get()->transform.set_position({ 2, 0, 0 });
		childCube.get()->transform.set_scale({ .5f, .5f, .5f });

		grandchildCube.get()->transform.set_parent(&childCube.get()->transform);
		grandchildCube.get()->transform.set_position({ 0, 2, 0 });
		grandchildCube.get()->transform.set_scale({ .5f, .5f, .5f });
	}

	void Renderer::update()
	{
		// Update camera and view matrix

		cubeXRotation += 0.2f;
		cubeYRotation += 0.4f;
		cube.get()->transform.set_rotation(vec3(cubeXRotation, cubeYRotation, 0));
	}

	void Renderer::render()
	{
		cube.get()->render();
		childCube.get()->render();
		grandchildCube.get()->render();
	}
}
