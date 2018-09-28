#pragma once

#include <core/Defines.hpp>
#include <view/Window.hpp>

namespace eng
{
	class Camera
	{
		friend class CameraController;

	public:
		static const glm::vec3 WorldUp;

	public:
		Camera();

		vec3 front() const { return m_front; }
		vec3 right() const { return m_right; }
		vec3 up() const { return m_up; }

		float fov() const { return m_fov; }
		void  fov(float value) { m_fov = value; }
		void  zoom(float offset);

		float aspectRatio() const { return m_aspectRatio; }
		void  aspectRatio(float value) { m_aspectRatio = value; }

		void lookAt(glm::vec3 target);

		// The view matrix for rendering.
		mat4 view() const;
		// The perspective projection matrix for rendering.
		mat4 projection() const;

	private:
		vec3 m_position = vec3(0.0f, 0.0f, 3.0f);

		vec3 m_front;
		vec3 m_right;
		vec3 m_up;
		
		float m_fov = 45.0f;
		float m_aspectRatio = 1.0f;

		mat4 m_view = mat4(1.0f);
		mat4 m_projection = mat4(1.0f);
	};
}

