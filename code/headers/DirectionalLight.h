
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include "Light.h"

namespace mg
{
	class DirectionalLight : public Light
	{

	private:

		vec3 direction;

	public:

		DirectionalLight(vec3 lightDirection, vec3 ambient, vec3 diffuse, vec3 specular)
		{
			setDirection(lightDirection);

			this->ambient = ambient;
			this->diffuse = diffuse;
			this->specular = specular;
		}

	public:

		const vec3 getDirection() const { return direction; }

		void setDirection(vec3 lightDirection)
		{
			direction = lightDirection;
		}
	};
}
