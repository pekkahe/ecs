#include <Precompiled.hpp>
#include <scene/CameraSystem.hpp>

#include <scene/CameraControlSystem.hpp>
#include <scene/Transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

using namespace eng;

CameraSystem::CameraSystem(Database& db) :
    m_cameraTable(db.createTable<Camera>())
{
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::update(const Scene&)
{
    query()
        .hasComponent<Updated>()
        .hasComponent<CameraControl>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId id, 
            const Updated&,
            const CameraControl& controller,
            Camera& camera)
    {
        vec3 front;
        front.x = cos(glm::radians(controller.pitch)) * cos(glm::radians(controller.yaw));
        front.y = sin(glm::radians(controller.pitch));
        front.z = cos(glm::radians(controller.pitch)) * sin(glm::radians(controller.yaw));
        glm::normalize(front);

        camera.align(front);
        camera.zoom(controller.zoom);
    });

    query()
        .hasComponent<Updated>()
        .hasComponent<Transform>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId id,
            const Updated&,
            const Transform& transform,
            Camera& camera)
    {
        camera.view = Camera::viewMatrix(camera, transform.position);
        camera.projection = Camera::projectionMatrix(camera);
    });

    query()
        .hasComponent<Transform>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId id,
            const Transform& transform,
            Camera& camera)
    {
        //camera.aspectRatio = aspectRatio;
    });
}

void CameraSystem::setAspectRatio(float aspectRatio)
{
    query()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId id,
            Camera& camera)
    {
        camera.aspectRatio = aspectRatio;
    });
}
