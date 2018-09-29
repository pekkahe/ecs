#pragma once

#include <core/Defines.hpp>
#include <view/Window.hpp>

namespace eng
{
	ENUM_FLAGS(CameraMovement)
	{
		None	 = 0,
		Forward  = 1 << 0,
		Backward = 1 << 1,
		Left	 = 1 << 2,
		Right	 = 1 << 3
	};

	class Camera;
	class CameraController : public Window::EventListener
	{
	public:
		float speed = 3.5f;
		float sensitivity = 0.05f;

	public:
		CameraController(
			Camera& camera, 
			std::shared_ptr<Window> window);

		void update();

		void onKeyInput(int key, int action, int mods) override;
		void onMouseButton(int button, int action, int mods) override;
		void onMouseCursor(double2 position) override;
		void onMouseScroll(double2 offset) override;
		void onWindowResize(int2 size) override;

	private:
		Camera& m_camera;
		std::shared_ptr<Window> m_window;
		CameraMovement m_movement = CameraMovement::None;

		bool m_firstMouse = true;
		bool m_enabled = false;
		int  m_enabledCursorDelay = 0;

		double m_lastX = 0.0f;
		double m_lastY = 0.0f;

		float m_yaw = -90.0f; // Default front is -z
		float m_pitch = 0.0f;
	};
}
