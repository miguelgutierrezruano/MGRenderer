
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
		// Forward y up

		return glm::lookAtLH(transform.get_position(), transform.get_position() + vec3(0, 0, 1), vec3(0, 1, 0));
		//return glm::inverse(transform.get_matrix());
	}

	glm::mat4 Camera::get_projection_matrix(float aspectRatio)
	{
		return glm::perspectiveLH_NO(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
	}
}