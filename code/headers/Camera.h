
// Distributed under MIT License
// @miguelgutierrezruano
// 2023

#pragma once

#include <glm\glm.hpp>

#include "Transform.h"

namespace mg
{
	class Camera
	{

	public:

		Transform transform;

	private:

		float fieldOfView;
		float nearPlane;
		float farPlane;

		float movementSpeed;
		float rotationSpeed;

	public:

		Camera(float fov, float near, float far);

	public:

		void setFov (float  fov) { fieldOfView =  fov; }
		void setNear(float near) {   nearPlane = near; }
		void setFar (float  far) {    farPlane =  far; }

		// Inverse camera transform
		glm::mat4 get_view_matrix();

		// Get projection matrix given by values
		glm::mat4 get_projection_matrix(float aspectRatio);

		void move_camera_x_axis(float value, float delta);
		void move_camera_z_axis(float value, float delta);

		void move_camera  (glm::vec2 positionDifference, float delta);
		void rotate_camera(glm::vec2 positionDifference, float delta);
	};
}
