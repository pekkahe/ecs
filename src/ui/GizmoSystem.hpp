#pragma once

#include <component/System.hpp>

#include <scene/Transform.hpp>
#include <ui/Gizmo.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class GizmoSystem : public System, public IWindowEventListener
    {
    public:
        ADD_COMPONENT_FUNCTION(Gizmo, m_gizmoTable);

    public:
        GizmoSystem(Database& db);
        ~GizmoSystem();

        void update(const Scene& scene) override;

    public:
        void onKeyInput(Window&, const InputEvent& input) override;

    private:
        TableRef<Gizmo> m_gizmoTable;

        ImGuizmo::OPERATION m_gizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        bool m_gizmoOperationChanged = false;
    };
}
