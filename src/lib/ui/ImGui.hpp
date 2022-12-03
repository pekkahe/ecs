#pragma once

#include <core/Datatypes.hpp>

#include <imgui.h>
#include <ImGuizmo.h>

namespace ecs
{
    namespace imgui
    {
        bool gizmoManipulate(
            mat4& model,
            const mat4& view,
            const mat4& projection,
            ImGuizmo::OPERATION operation,
            ImGuizmo::MODE mode);
    }
}
