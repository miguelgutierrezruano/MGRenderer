
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <iostream>
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
		mainCamera(45, 0.1f, 150.f),
		light(vec3(0.05f), vec3(1.f), vec3(0.5f)),
		directionalLight(vec3(1, 0, 0), vec3(0.05f), vec3(221.f / 255, 84.f / 255, 28.f / 255), vec3(0.0f))
	{
		mainCamera.transform.set_position({ 0, 8, -30 });

		// Get from camera get projection
		glm::mat4 projection = mainCamera.get_projection_matrix((float)width / (float)height);

		// Model shader
		modelShader = make_shared<Shader>("../code/shaders/PhongTexture.shader");

		modelShader.get()->bind();
		modelShader.get()->setUniformMat4f("projection", projection);

		modelShader.get()->setUniform1f("material.shininess", 32.f);

		// Basic shader (remove)
		basicShader = make_shared<Shader>("../code/shaders/Basic.shader");

		basicShader.get()->bind();
		basicShader.get()->setUniformMat4f("projection", projection);

		// Skybox shader
		skyboxShader = make_shared<Shader>("../code/shaders/Skybox.shader");

		skyboxShader.get()->bind();
		skyboxShader.get()->setUniformMat4f("projection", projection);

		auto journey = make_shared<Model>("../resources/models/journey/journey.fbx");
		auto desert = make_shared<Model>("../resources/models/desert/desert.fbx");
		models.insert(std::pair<std::string, shared_ptr<Model>>("journey", journey));
		models.insert(std::pair<std::string, shared_ptr<Model>>("desert", desert));

		models["journey"].get()->transform.set_parent(&desert.get()->transform);
		desert.get()->transform.set_position(vec3(0, -2, 0));
		desert.get()->transform.set_scale(vec3(0.2f));

		journey.get()->transform.set_position(vec3(0, 23, 0));

		light.transform.set_parent(&desert.get()->transform);
		light.transform.set_position(vec3(0, 80, -30));

		modelShader.get()->bind();
		modelShader.get()->setUniform3f("dirLight.direction", directionalLight.getDirection());
		modelShader.get()->setUniform3f("dirLight.ambient", directionalLight.getAmbient());
		modelShader.get()->setUniform3f("dirLight.diffuse", directionalLight.getDiffuse());
		modelShader.get()->setUniform3f("dirLight.specular", directionalLight.getSpecular());

		modelShader.get()->setUniform3f("pointLight.position", light.transform.get_world_position());
		modelShader.get()->setUniform3f("pointLight.ambient", light.getAmbient());
		modelShader.get()->setUniform3f("pointLight.diffuse", light.getDiffuse());
		modelShader.get()->setUniform3f("pointLight.specular", light.getSpecular());

		modelShader.get()->setUniform1f("material.shininess", 0.2f);

		modelShader.get()->setUniform1f("pointLight.constant", 1.0f);
		modelShader.get()->setUniform1f("pointLight.linear", 0.07f);
		modelShader.get()->setUniform1f("pointLight.quadratic", 0.017f);
	}

	void Renderer::update(float delta)
	{
		update_camera(delta);

		glm::mat4 view = mainCamera.get_view_matrix();
		modelShader->bind();
		modelShader->setUniformMat4f("view", view);
		modelShader->setUniform3f("viewPos", mainCamera.transform.get_position());
		modelShader->setUniform3f("pointLight.position", light.transform.get_world_position());

		basicShader->bind();
		basicShader->setUniformMat4f("view", view);

		// View for skybox without translation
		view = glm::mat4(glm::mat3(view));
		skyboxShader.get()->bind();
		skyboxShader.get()->setUniformMat4f("view", view);

		modelYRotation += 10.f * delta;
		models["desert"].get()->transform.set_rotation(vec3(0, modelYRotation, 0));
	}

	void Renderer::render()
	{
		skybox.render(skyboxShader);

		for (auto& [name, model] : models)
		{
			model.get()->render(modelShader);
		}

		//light.render(basicShader);
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
