
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

		DirectionalLight()
		{
			direction = vec3(0, 1, 0);
		}

		DirectionalLight(vec3 lightDirection)
		{
			setDirection(lightDirection);
		}

	public:

		void setDirection(vec3 lightDirection)
		{
			direction = lightDirection;
		}
	};
}
