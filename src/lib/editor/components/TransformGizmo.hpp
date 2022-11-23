#pragma once

#include <core/ecs/IComponent.hpp>

#define IMGUI_USER_CONFIG <ui/ImConfig.hpp>
#include <imgui.h>
#include <ImGuizmo.h>

namespace ecs
{
    class TransformGizmo : public IComponent
    {
    public:
        ImGuizmo::OPERATION operation = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE mode = ImGuizmo::MODE::LOCAL;
    };
}
