#pragma once

#include <imgui.h>
#include <ImGuizmo.h>

namespace ecs
{
    struct Hovered
    {
    };

    struct Selected
    { 
    };

    struct TransformGizmo
    {
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE mode = ImGuizmo::MODE::LOCAL;
    };
}