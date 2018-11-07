#include <Precompiled.hpp>
#include <scene/TransformSystem.hpp>

#include <scene/Camera.hpp>
#include <scene/CameraControl.hpp>
#include <scene/Scene.hpp>
#include <scene/Selected.hpp>
#include <ui/ImGui.hpp>

using namespace eng;

TransformSystem::TransformSystem(
    Database& db,
    std::shared_ptr<Window> window) :
    m_transformTable(db.createTable<Transform>()),
    m_transformGizmoTable(db.createTable<TransformGizmo>()),
    m_transformGizmoController(std::make_shared<TransformGizmoController>())
{
    window->addEventListener(m_transformGizmoController);
}

TransformSystem::~TransformSystem()
{
}

void TransformSystem::update(const Scene&)
{
    // Move camera controlled transforms
    // todo: we could extend CameraControl into a "TransformControl" 
    // component which allows input and program control to any entity
    // with a transform, with this it might be best to expect that the
    // front vector is precomputed
    query()
        .hasComponent<Updated>()
        .hasComponent<CameraControl>()
        .hasComponent<Transform>(m_transformTable)
        .execute([&](
            EntityId, 
            const Updated&,
            const CameraControl& control,
            Transform& transform)
    {
        vec3 cameraFront;
        cameraFront.x = cos(glm::radians(control.pitch)) * cos(glm::radians(control.yaw));
        cameraFront.y = sin(glm::radians(control.pitch));
        cameraFront.z = cos(glm::radians(control.pitch)) * sin(glm::radians(control.yaw));
        glm::normalize(cameraFront);

        vec3 cameraRight = glm::normalize(glm::cross(cameraFront, Camera::WorldUp));
        vec3 cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));
        
        float cameraSpeed = control.speed * Time::deltaTime();

        // Move camera
        if (control.isMoving(CameraMovement::Forward))
        {
            transform.position += cameraFront * cameraSpeed;
        }

        if (control.isMoving(CameraMovement::Backward))
        {
            transform.position -= cameraFront * cameraSpeed;
        }

        if (control.isMoving(CameraMovement::Left))
        {
            transform.position -= glm::normalize(
                glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }

        if (control.isMoving(CameraMovement::Right))
        {
            transform.position += glm::normalize(
                glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        }

        // Rotate camera
        transform.rotation = glm::quatLookAt(cameraFront, Camera::WorldUp);
    });

    auto camera = query().find<Camera>();
    assert(camera != nullptr && "No camera in scene");

    // Move gizmo manipulated transforms which are selected
    query()
        .hasComponent<Selected>()
        .hasComponent<Transform>(m_transformTable)
        .hasComponent<TransformGizmo>(m_transformGizmoTable)
        .execute([&](
            EntityId id, 
            const Selected&,
            Transform& transform,
            TransformGizmo& transformGizmo)
    {
        m_transformGizmoController->update(transformGizmo);

        mat4 modelMatrix = transform.modelMatrix();

        if (imgui::gizmoManipulate(
            modelMatrix,
            camera->viewMatrix,
            camera->projectionMatrix,
            transformGizmo.operation))
        {
            // Decompose manipulated values back into component
            glm::decompose(
                modelMatrix,
                transform.scale,
                transform.rotation,
                transform.position,
                vec3(),
                vec4());

            markUpdated(id);
        }
    });
}

