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
    front(vec3(0.0f, 0.0f, -1.0f)),
    right(glm::normalize(glm::cross(front, WorldUp))),
    up(glm::normalize(glm::cross(right, front)))
{
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::zoom(float offset)
{
    if (fov >= 1.0f && fov <= 45.0f)
    {
        fov -= offset;
    }

    if (fov <= 1.0f)
    {
        fov = 1.0f;
    }
    else if (fov >= 45.0f)
    {
        fov = 45.0f;
    }

    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::lookAt(vec3 from, glm::vec3 target)
{
    front = glm::normalize(target - from);
    right = glm::normalize(glm::cross(front, WorldUp));
    up	= glm::normalize(glm::cross(right, front));
}

void Camera::computeViewMatrix(vec3 position)
{
    view = glm::lookAt(position, position + front, up);
}
