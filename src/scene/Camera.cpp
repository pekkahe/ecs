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

const vec3 Camera::WorldUp = vec3(0.0f, 1.0f, 0.0f);

Camera::Camera() :
    front(vec3(0.0f, 0.0f, -1.0f)),
    right(glm::normalize(glm::cross(front, WorldUp))),
    up(glm::normalize(glm::cross(right, front)))
{
}

void Camera::align(vec3 front_)
{
    front = front_;
    right = glm::normalize(glm::cross(front, Camera::WorldUp));
    up    = glm::normalize(glm::cross(right, front));
}

void Camera::zoom(float offset)
{
    if (fov >= 1.0f && fov <= 45.0f)
    {
        fov -= offset;

        math::clamp(fov, 1.0f, 45.0f);
    }
}

mat4 Camera::viewMatrix(const Camera& camera, vec3 position)
{
    return glm::lookAt(position, position + camera.front, camera.up);
}

mat4 Camera::projectionMatrix(const Camera & camera)
{
    return glm::perspective(glm::radians(camera.fov), camera.aspectRatio, 0.1f, 100.0f);
}