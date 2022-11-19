#pragma once

#include <core/ecs/IComponent.hpp>

#include <ImGuizmo.h>

namespace eng
{
    class TransformGizmo : public IComponent
    {
    public:
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE mode = ImGuizmo::MODE::LOCAL;
    };
}
