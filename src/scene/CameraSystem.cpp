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
        .hasComponent<Transform>()
        .hasComponent<CameraControl>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId id, 
            const Transform& transform,
            const CameraControl& controller,
            Camera& camera)
    {
        camera.zoom(controller.zoom);
        camera.lookAt(transform.position, transform.position + controller.front);
        camera.computeViewMatrix(transform.position);
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
