#include <Precompiled.hpp>
#include <scene/CameraSystem.hpp>
#include <scene/components/Transform.hpp>

using namespace eng;

CameraSystem::CameraSystem(
    Database& db,
    std::shared_ptr<Window> window) :
    m_cameraTable(db.createTable<Camera>()),
    m_cameraControlTable(db.createTable<CameraControl>()),
    m_cameraController(std::make_shared<CameraController>(window->size()))
{
    window->addEventListener(m_cameraController);
    window->onWindowResize([&](int2 size)
    {
        setAspectRatio(static_cast<float>(size.x) / size.y);
    });
}

CameraSystem::~CameraSystem()
{
}

void CameraSystem::update(const Scene&)
{
    m_cameraControlTable.forEach(
        [&](EntityId id, CameraControl& control) 
    {
        if (m_cameraController->update(control))
        {
            markUpdated(id);
        }
    });

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
        
        camera.viewMatrix = glm::inverse(model);
        camera.projectionMatrix = glm::perspective(
            glm::radians(camera.fov),
            camera.aspectRatio,
            camera.nearPlane,
            camera.farPlane);
    });
}

void CameraSystem::setAspectRatio(float aspectRatio)
{
    // TODO: Create Window/WindowState component? Could use Updated, Added...
    query()
        .hasComponent<Camera>(m_cameraTable)
        .execute([&](
            EntityId,
            Camera& camera)
    {
        camera.aspectRatio = aspectRatio;
    });
}
