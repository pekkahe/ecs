#include <Precompiled.hpp>
#include <scene/TransformSystem.hpp>

#include <component/Query.hpp>
#include <scene/Scene.hpp>
#include <scene/Camera.hpp>
#include <scene/CameraControlSystem.hpp>

#include <ui/GizmoSystem.hpp>
#include <ui/ImGui.hpp>

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

#include <imgui.h>
#include <ImGuizmo.h>

using namespace eng;

TransformSystem::TransformSystem(Database& db) :
    m_transformTable(db.createTable<Transform>())
{
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::update(const Scene&)
{
    // Move input controlled cameras
    query()
        .hasComponent<Updated>()
        .hasComponent<Camera>()
        .hasComponent<CameraControl>()
        .hasComponent<Transform>(m_transformTable)
        .execute([&](
            EntityId, 
            const Updated&,
            const Camera& camera, 
            const CameraControl& controller,
            Transform& transform)
    {
        float cameraSpeed = controller.speed * Time::deltaTime();

        auto checkMovement = [&controller](const CameraMovement& movement)
        {
            return (controller.movement & movement) == movement;
        };

        if (checkMovement(CameraMovement::Forward))
        {
            transform.position += camera.front * cameraSpeed;
        }

        if (checkMovement(CameraMovement::Backward))
        {
            transform.position -= camera.front * cameraSpeed;
        }

        if (checkMovement(CameraMovement::Left))
        {
            transform.position -= glm::normalize(
                glm::cross(camera.front, camera.up)) * cameraSpeed;
        }

        if (checkMovement(CameraMovement::Right))
        {
            transform.position += glm::normalize(
                glm::cross(camera.front, camera.up)) * cameraSpeed;
        }
    });

    auto camera = query().find<Camera>();
    assert(camera != nullptr && "No camera in scene");

    // Move gizmo manipulated transforms
    query()
        .hasComponent<Gizmo>()
        .hasComponent<Transform>(m_transformTable)
        .execute([&](
            EntityId id, 
            const Gizmo& gizmo, 
            Transform& transform)
    {
        mat4 modelMatrix = transform.modelMatrix();

        imgui::gizmoManipulate(
            modelMatrix,
            camera->view,
            camera->projection,
            gizmo.operation);

        if (!ImGuizmo::IsUsing())
        {
            return;
        }

        // Decompose manipulated values back into component
        glm::decompose(
            modelMatrix,
            transform.scale,
            transform.rotation,
            transform.position,
            vec3(),
            vec4());

        markUpdated(id);
    });
}

