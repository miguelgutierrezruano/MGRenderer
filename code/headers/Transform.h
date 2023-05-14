
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <glm/glm.hpp>

using namespace glm;

namespace mg
{
	class Transform
	{

	private: 

		Transform* parent;

		vec3 position;
		vec3 rotation;
		vec3 scale;

	public:

		Transform();

		Transform(Transform* parentTransform);

		Transform(Transform* parentTransform, const vec3 startPosition, const vec3 startRotation, const vec3 startScale);

		const vec3 get_position() { return position; }
		const vec3 get_rotation() { return rotation; }
		const vec3 get_scale() { return scale; }

		const vec3 get_world_position();

		void set_position(vec3 newPosition) { position = newPosition; }
		void set_rotation(vec3 newRotation) { rotation = newRotation; }
		void set_scale(vec3 newScale) { scale = newScale; }

		void set_parent(Transform* parentTransform) { parent = parentTransform; }

		const vec3 get_forward();
		const vec3 get_right();
		const vec3 get_up();

		const mat4 get_matrix();
	};
}
