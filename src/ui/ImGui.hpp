#pragma once

#include <core/Datatypes.hpp>

#include <ImGuizmo.h>

namespace eng
{
    namespace imgui
    {
        void init();

        void deinit();

        void startFrame();

        void endFrame();

        void gizmoManipulate(
            mat4& model,
            const mat4& view, const
            mat4& projection,
            ImGuizmo::OPERATION operation);
    }
}
