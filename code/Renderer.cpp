
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Renderer.h"

namespace mg
{
	Renderer::Renderer(unsigned int width, unsigned int height)
		: cubeXRotation(0), cubeYRotation(0)
	{
		// Get from camera transform
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0, 0, -8.f));

		// Get from camera get projection
		glm::mat4 projection = glm::perspective(glm::radians(45.f), (float)width / (float)height, 0.1f, 50.f);

		shader = make_shared<Shader>("../code/shaders/Basic.shader");

		shader.get()->bind();
		shader.get()->setUniformMat4f("view", view);
		shader.get()->setUniformMat4f("projection", projection);

		cube = make_shared<Mesh>(shader);
		childCube = make_shared<Mesh>(shader);

		childCube.get()->transform.set_parent(&cube.get()->transform);
		childCube.get()->transform.set_position({ 2, 0, 0 });
		childCube.get()->transform.set_scale({ .5f, .5f, .5f });
	}

	void Renderer::update()
	{
		cubeXRotation += 0.2f;
		cubeYRotation += 0.4f;
		cube.get()->transform.set_rotation(vec3(cubeXRotation, cubeYRotation, 0));
	}

	void Renderer::render()
	{
		cube.get()->render();
		childCube.get()->render();
	}
}
