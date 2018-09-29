#include <Precompiled.hpp>
#include <scene/CameraController.hpp>
#include <scene/Camera.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

CameraController::CameraController(
	Camera& camera, 
	std::shared_ptr<Window> window) :
	m_camera(camera),
	m_window(std::move(window))
{
	auto windowSize = m_window->size();

	m_lastX = static_cast<double>(windowSize.x) / 2;
	m_lastY = static_cast<double>(windowSize.y) / 2;
}

void CameraController::update()
{
	if (!m_enabled)
	{
		return;
	}

	float cameraSpeed = speed * Time::deltaTime();

	auto checkMovement = [this](CameraMovement movement)
	{
		return (m_movement & movement) == movement;
	};

	if (checkMovement(CameraMovement::Forward))
	{
		m_camera.m_position += m_camera.front() * cameraSpeed;
	}

	if (checkMovement(CameraMovement::Backward))
	{
		m_camera.m_position -= m_camera.front() * cameraSpeed;
	}

	if (checkMovement(CameraMovement::Left))
	{
		m_camera.m_position -= glm::normalize(
			glm::cross(m_camera.front(), m_camera.up())) * cameraSpeed;
	}

	if (checkMovement(CameraMovement::Right))
	{
		m_camera.m_position += glm::normalize(
			glm::cross(m_camera.front(), m_camera.up())) * cameraSpeed;
	}
}

void CameraController::onKeyInput(int key, int action, int mods)
{
	auto updateMovement = [&](int ifKey, CameraMovement movement)
	{
		if (key == ifKey)
		{
			if (action != GLFW_RELEASE)
			{
				m_movement |= movement;
			}
			else
			{
				m_movement &= ~movement;
			}
		}
	};

	updateMovement(GLFW_KEY_W, CameraMovement::Forward);
	updateMovement(GLFW_KEY_S, CameraMovement::Backward);
	updateMovement(GLFW_KEY_A, CameraMovement::Left);
	updateMovement(GLFW_KEY_D, CameraMovement::Right);
}

void CameraController::onMouseButton(int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_enabled = action == GLFW_PRESS;
		m_enabledCursorDelay = m_enabled ? 1 : 0;

		m_window->captureMouseCursor(m_enabled);
	}
}

void CameraController::onMouseCursor(double2 screenPosition)
{
	if (m_firstMouse)
	{
		m_lastX = screenPosition.x;
		m_lastY = screenPosition.y;
		m_firstMouse = false;
	}

	// Reversed y-coordinates since range is from bottom to top
	double xoffset = screenPosition.x - m_lastX;
	double yoffset = m_lastY - screenPosition.y;

	// Store screen position always to keep offset calculation up-to-date
	m_lastX = screenPosition.x;
	m_lastY = screenPosition.y;

	if (!m_enabled)
	{
		return;
	}

	// When toggling mouse cursor capture, GLFW does its own saving and restoring of
	// the cursor position. The position appears to jump incorrectly in some cases right
	// after mouse capture is enabled. To prevent this from wildly changing our camera
	// rotation, we ignore the one excessive offset calculation after the change.

	if (m_enabledCursorDelay > 0)
	{
		m_enabledCursorDelay--;
		return;
	}

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw   += static_cast<float>(xoffset);
	m_pitch += static_cast<float>(yoffset);

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}
	else if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
	front.y = sin(glm::radians(m_pitch));
	front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
	glm::normalize(front);

	m_camera.lookAt(m_camera.m_position + front);
}

void CameraController::onMouseScroll(double2 offset)
{
	m_camera.zoom(static_cast<float>(offset.y));
}

void CameraController::onWindowResize(int2 size)
{
	m_camera.aspectRatio(static_cast<float>(size.x) / size.y);
}
