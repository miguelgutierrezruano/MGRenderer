
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace mg
{
	Camera::Camera(float fov, float near, float far)
		: fieldOfView(fov), nearPlane(near), farPlane(far)
	{
		
	}

	glm::mat4 Camera::get_view_matrix()
	{
		return glm::inverse(transform.get_matrix());
	}

	glm::mat4 Camera::get_projection_matrix(float aspectRatio)
	{
		return glm::perspective(glm::radians(45.f), aspectRatio, 0.1f, 50.f);
	}
}