#pragma once

#include <component/System.hpp>
#include <scene/TransformGizmo.hpp>

namespace eng
{
    class EditorSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(TransformGizmo, m_transformGizmoTable);

    public:
        EditorSystem(Database& db);
        ~EditorSystem();

        void update(const Scene& scene) override;

    private:
        TableRef<TransformGizmo> m_transformGizmoTable;
    };
}