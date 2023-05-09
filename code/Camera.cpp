
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"

namespace mg
{
	Camera::Camera(float fov, float near, float far)
		: fieldOfView(fov), nearPlane(near), farPlane(far),
		movementSpeed(20)
	{
		
	}

	glm::mat4 Camera::get_view_matrix()
	{
		return glm::lookAtLH(transform.get_position(), transform.get_position() + transform.get_forward(), transform.get_up());
	}

	glm::mat4 Camera::get_projection_matrix(float aspectRatio)
	{
		return glm::perspectiveLH_NO(glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);
	}

	void Camera::move_camera_x_axis(float value, float delta)
	{
		// I think since its a left handed coord system right becomes left?

		vec3 pos = transform.get_position();
		transform.set_position(pos + transform.get_right() * -value * movementSpeed * delta);
	}

	void Camera::move_camera_z_axis(float value, float delta)
	{
		vec3 pos = transform.get_position();
		transform.set_position(pos + transform.get_forward() * value * movementSpeed * delta);
	}
}