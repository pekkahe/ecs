#include <Precompiled.hpp>
#include <scene/CameraController.hpp>
#include <scene/Camera.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

CameraController::CameraController(
	Camera& camera, 
	int2 viewportSize) :
	m_camera(camera),
	m_lastX((float) viewportSize.x / 2),
	m_lastY((float) viewportSize.y / 2)
{
}

void CameraController::onKeyPress(int keyCode)
{
	float cameraSpeed = 2.5f * Time::deltaTime();

	if (keyCode == GLFW_KEY_W)
	{
		m_camera.m_position += m_camera.front() * cameraSpeed;
	}
	else if (keyCode == GLFW_KEY_S)
	{
		m_camera.m_position -= m_camera.front() * cameraSpeed;
	}
	else if (keyCode == GLFW_KEY_A)
	{
		m_camera.m_position -= glm::normalize(
			glm::cross(m_camera.front(), m_camera.up())) * cameraSpeed;
	}
	else if (keyCode == GLFW_KEY_D)
	{
		m_camera.m_position += glm::normalize(
			glm::cross(m_camera.front(), m_camera.up())) * cameraSpeed;
	}
}

void CameraController::onMouseCursor(double2 screenPosition)
{
	if (m_firstMouse)
	{
		m_lastX = static_cast<float>(screenPosition.x);
		m_lastY = static_cast<float>(screenPosition.y);
		m_firstMouse = false;
	}

	// Reversed y-coordinates since range is from bottom to top
	float xoffset = static_cast<float>(screenPosition.x) - m_lastX;
	float yoffset = m_lastY - static_cast<float>(screenPosition.y);

	m_lastX = static_cast<float>(screenPosition.x);
	m_lastY = static_cast<float>(screenPosition.y);

	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

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
