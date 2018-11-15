#pragma once

#include <core/Defines.hpp>

namespace eng
{
    ENUM_FLAGS(InputAction)
    {
        None = 0,
        Camera_MoveForward = 1 << 0,
        Camera_MoveBackward = 1 << 1,
        Camera_MoveLeft = 1 << 2,
        Camera_MoveRight = 1 << 3,
        Camera_Zoom = 1 << 4,
        Camera_ToggleControl = 1 << 5,
        Gizmo_ChangeOperation = 1 << 6,
        Gizmo_ChangeMode = 1 << 7,
        Entity_CreateCube = 1 << 8,
        Entity_Delete = 1 << 9,
        Quit = 1 << 10,
    };

    class InputBindings
    {

    };

    class InputActions
    {
    public:
        bool check(InputAction action) const;
    };
}
