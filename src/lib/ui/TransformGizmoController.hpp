#pragma once

#include <scene/TransformGizmo.hpp>

#include <ui/Window.hpp>

namespace eng
{
    class TransformGizmoController : public IWindowEventListener
    {
    public:
        bool update(TransformGizmo& gizmo);

        void onKeyInput(Window&, const InputEvent& input) override;

    private:
        bool m_updated = false;

        ImGuizmo::OPERATION m_operation = ImGuizmo::OPERATION::TRANSLATE;
    };
}
