
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace mg
{
	Transform::Transform()
		: position(), rotation(), scale(1.f, 1.f, 1.f), parent(nullptr)
	{

	}

	Transform::Transform(Transform* parentTransform)
		: position(), rotation(), scale(1.f, 1.f, 1.f), parent(parentTransform)
	{
	}

	Transform::Transform(Transform* parentTransform, const vec3 startPosition, const vec3 startRotation, const vec3 startScale)
		: position(startPosition), rotation(startRotation), scale(startScale), parent(parentTransform)
	{

	}

	const mat4 Transform::get_matrix()
	{
		mat4 identity = mat4(1);
		mat4 scalingMatrix = glm::scale(identity, scale);

		// Rotate based on euler angles
		mat4 xRotate = glm::rotate(identity, radians(rotation.x), vec3(1.f, 0.f, 0.f));
		mat4 yRotate = glm::rotate(identity, radians(rotation.y), vec3(0.f, 1.f, 0.f));
		mat4 zRotate = glm::rotate(identity, radians(rotation.z), vec3(0.f, 0.f, 1.f));

		mat4 rotationMatrix = zRotate * yRotate * xRotate;

		mat4 translationMatrix = glm::translate(identity, position);

		mat4 parentMatrix = mat4(1);

		if (parent != nullptr)
			parentMatrix = parent->get_matrix();

		return parentMatrix * translationMatrix * rotationMatrix * scalingMatrix;
	}
}