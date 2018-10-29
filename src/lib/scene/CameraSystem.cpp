#include <Precompiled.hpp>
#include <scene/CameraSystem.hpp>

#include <scene/Transform.hpp>

using namespace eng;

CameraSystem::CameraSystem(
    Database& db,
    std::shared_ptr<Window> window) :
    m_cameraTable(db.createTable<Camera>()),
    m_cameraControlTable(db.createTable<CameraControl>()),
    m_cameraController(std::make_shared<CameraController>(window->size()))
{
    window->addEventListener(m_cameraController);
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::update(const Scene&)
{
    auto cameraControls = m_cameraControlTable.ids();
    if (!cameraControls.empty())
    {
        auto cameraControlId = cameraControls[0];
        auto cameraControl = m_cameraControlTable[cameraControlId];

        if (m_cameraController->update(*cameraControl))
        {
            markUpdated(cameraControlId);
        }
    }

    query()
        .hasComponent<Updated>()
        .hasComponent<CameraControl>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId, 
            const Updated&,
            const CameraControl& control,
            Camera& camera)
    {
        camera.fov -= control.zoom;
        camera.fov = math::clamp(camera.fov, 10.0f, 45.0f);
    });

    query()
        .hasComponent<Updated>()
        .hasComponent<Transform>()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId,
            const Updated&,
            const Transform& transform,
            Camera& camera)
    {
        mat4 model = transform.modelMatrix();
        
        // To get the camera's view matrix, 
        // we just inverse its model matrix
        camera.viewMatrix = glm::inverse(model);

        camera.projectionMatrix = glm::perspective(
            glm::radians(camera.fov),
            camera.aspectRatio,
            camera.nearPlane,
            camera.farPlane);
    });

    //query()
    //    .hasComponent<Transform>()
    //    .hasComponent<Camera>(m_cameraTable)
    //    .execute([&](
    //        EntityId id,
    //        const Transform& transform,
    //        Camera& camera)
    //{
    //    camera.aspectRatio = aspectRatio;
    //});
}

void CameraSystem::setAspectRatio(float aspectRatio)
{
    query()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId,
            Camera& camera)
    {
        camera.aspectRatio = aspectRatio;
    });
}
