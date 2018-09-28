#pragma once

#include <core/Defines.hpp>
#include <view/Window.hpp>

namespace eng
{
	class Camera;
	class CameraController : public Window::EventListener
	{
	public:
		float sensitivity = 0.05f;

	public:
		CameraController(Camera& camera, int2 viewportSize);

		void onKeyPress(int keyCode) override;
		void onMouseCursor(double2 position) override;
		void onMouseScroll(double2 offset) override;
		void onWindowResize(int2 size) override;

	private:
		Camera& m_camera;

		float m_lastX;
		float m_lastY;
		float m_yaw = -90.0f; // Default front is -z
		float m_pitch = 0.0f;
		bool  m_firstMouse = true;
	};
}
