#pragma once

#include <component/System.hpp>
#include <scene/Transform.hpp>
//#include <scene/TransformGizmo.hpp>
//#include <ui/TransformGizmoController.hpp>

namespace eng
{
    class TransformSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Transform, m_transformTable);
        //ADD_COMPONENT_FUNCTION(TransformGizmo, m_transformGizmoTable);

    public:
        TransformSystem(Database& db);
        ~TransformSystem();

        void update(const Scene& scene) override;

    private:
        TableRef<Transform> m_transformTable;
        //TableRef<TransformGizmo> m_transformGizmoTable;
        //std::shared_ptr<TransformGizmoController> m_transformGizmoController;
    };
}