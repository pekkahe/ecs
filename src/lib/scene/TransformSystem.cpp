#include <Precompiled.hpp>
#include <scene/TransformSystem.hpp>

#include <scene/Camera.hpp>
#include <scene/CameraControl.hpp>
#include <scene/Scene.hpp>
#include <scene/Selected.hpp>
#include <ui/ImGui.hpp>

#include <ImGuizmo.h>

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
    // Move and rotate camera
    // TODO: Consider extending CameraControl into a "TransformControl" component 
    // which allows input and program control to any entity with a transform.
    // With this it might be wise to expect that the front vector is precomputed.
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

        transform.rotation = glm::quatLookAt(cameraFront, Camera::WorldUp);
    });

    auto camera = query().find<Camera>();
    assert(camera != nullptr && "No camera in scene");

    // Compute bounds for selected objects
    AABB selectedBounds;
    query()
        .hasComponent<Selected>()
        .hasComponent<Mesh>()
        .hasComponent<Transform>()
        .execute([&](
            EntityId,
            const Selected&,
            const Mesh&,
            const Transform& transform)
    {
        selectedBounds.expand(transform.position);
    });

    // Apply transform gizmo for selected objects
    query()
        .hasComponent<Selected>()
        .hasComponent<Transform>(m_transformTable)
        .hasComponent<TransformGizmo>(m_transformGizmoTable)
        .execute([&](
            EntityId,
            const Selected&,
            Transform& transform,
            TransformGizmo& transformGizmo)
    {
        // Update gizmo configuration
        m_transformGizmoController->update(transformGizmo);

        // Move gizmo to selection center
        transform.position = selectedBounds.center();

        Transform previousTransform(transform);
        mat4 modelMatrix(transform.modelMatrix());
        
        // Manipulate the gizmo's model matrix with ImGuizmo
        bool gizmoUsed = imgui::gizmoManipulate(
            modelMatrix,
            camera->viewMatrix,
            camera->projectionMatrix,
            transformGizmo.operation,
            transformGizmo.mode);
        if (!gizmoUsed)
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

        // Compute delta transform
        Transform delta;
        delta.position = transform.position - previousTransform.position;
        delta.rotation = transform.rotation * glm::inverse(previousTransform.rotation);
        delta.scale = transform.scale - previousTransform.scale;

        // Apply delta transform to selected objects
        query()
            .hasComponent<Selected>()
            .hasComponent<Mesh>()
            .hasComponent<Transform>(m_transformTable)
            .execute([&](
                EntityId meshId,
                const Selected&,
                const Mesh&,
                Transform& meshTransform)
        {
            // Note the order of addition for rotation
            meshTransform.position += delta.position;
            meshTransform.rotation = delta.rotation * meshTransform.rotation; 
            meshTransform.scale += delta.scale;

            markUpdated(meshId);
        });
    });
}
