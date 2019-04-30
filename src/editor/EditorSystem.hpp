#pragma once

#include <system/System.hpp>
#include <editor/Hovered.hpp>
#include <editor/Selected.hpp>
#include <editor/TransformGizmo.hpp>

namespace eng
{
    class EditorSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Hovered, m_hoveredTable);
        ADD_COMPONENT_FUNCTION(Selected, m_selectedTable);
        ADD_COMPONENT_FUNCTION(TransformGizmo, m_transformGizmoTable);

    public:
        EditorSystem(Database& db);
        ~EditorSystem();

        void update(const Scene& scene) override;

    private:
        TableRef<Hovered> m_hoveredTable;
        TableRef<Selected> m_selectedTable;
        TableRef<TransformGizmo> m_transformGizmoTable;
    };
}