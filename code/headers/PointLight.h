
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <memory>

#include "Transform.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"

using std::shared_ptr;

namespace mg
{
	class PointLight
	{

	public:

		Transform transform;

	protected:

		// Color for each lightning 
		vec3 ambient;
		vec3 diffuse;
		vec3 specular;

	private:

		// Cube to represent light position
		static float vertices[];

		VertexArray  vao;
		VertexBuffer vbo;

	public:

		PointLight(vec3 ambient, vec3 diffuse, vec3 specular);

	protected:

		PointLight();

	public:

		void render(shared_ptr< Shader > shader);

		const vec3 getAmbient () const { return  ambient; }
		const vec3 getDiffuse () const { return  diffuse; }
		const vec3 getSpecular() const { return specular; }
	};
}