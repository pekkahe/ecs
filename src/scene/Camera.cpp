#include <Precompiled.hpp>
#include <scene/Camera.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace eng;

// By convention, OpenGL is a right-handed system:
// +x = right
// +y = up
// +z = back
// -x = left
// -y = down
// -z = front
const glm::vec3 Camera::WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

Camera::Camera() :
    m_front(vec3(0.0f, 0.0f, -1.0f)),
    m_right(glm::normalize(glm::cross(m_front, WorldUp))),
    m_up(glm::normalize(glm::cross(m_right, m_front)))
{
}

void Camera::zoom(float offset)
{
    if (m_fov >= 1.0f && m_fov <= 45.0f)
    {
        m_fov -= offset;
    }

    if (m_fov <= 1.0f)
    {
        m_fov = 1.0f;
    }
    else if (m_fov >= 45.0f)
    {
        m_fov = 45.0f;
    }
}

void Camera::lookAt(glm::vec3 target)
{
    m_front = glm::normalize(target - m_position);
    m_right = glm::normalize(glm::cross(m_front, WorldUp));
    m_up	= glm::normalize(glm::cross(m_right, m_front));
}

glm::mat4 Camera::view() const
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::projection() const
{
    return glm::perspective(glm::radians(m_fov), m_aspectRatio, 0.1f, 100.0f);
}