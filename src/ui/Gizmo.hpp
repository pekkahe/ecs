#pragma once

#include <component/IComponent.hpp>

#include <ImGuizmo.h>

namespace eng
{
    class Gizmo : public IComponent
    {
    public:
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
    };
}
