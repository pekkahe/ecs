#pragma once

#include <core/ecs/System.hpp>
// TODO: Scene.components.hpp
// TODO: Editor.components.hpp
#include <editor/Selected.hpp>
#include <editor/TransformGizmo.hpp>
#include <scene/Camera.hpp>
#include <scene/CameraControl.hpp>
#include <scene/Transform.hpp>

namespace eng
{
    class AABB;

    class TransformSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Transform, m_transformTable);

    public:
        TransformSystem(Database& db);
        ~TransformSystem();

        void update(const Scene& scene) override;

        
        void schedule(Scheduler& scheduler);

        void transformCamera(
            const CameraControl& cameraControl,
            Transform& transform);

        Transform transformGizmo(
            const Camera& camera,
            const AABB& selectedBounds,
            const TransformGizmo& transformGizmo, 
            Transform& transform);

        // QUERY:  'translateCamera'
        // READS:  (Updated), CameraControl, Transform
        // WRITES: Transform

        // QUERY:  'computeSelectedBounds'
        // READS:  Selected, Transform
        // WRITES: <bounds>

        // QUERY:  'translateSelected'
        // READS:  <bounds>, Camera, TransformGizmo, Transform, Selected
        // WRITES: Transform, (Updated)

    private:
        TableRef<Transform> m_transformTable;
    };
}