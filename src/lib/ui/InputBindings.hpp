#pragma once

#include <core/Defines.hpp>

namespace eng
{
    ENUM_FLAGS(EngineAction)
    {
        None = 0,
        CameraMoveForward = 1 << 0,
        CameraMoveBackward = 1 << 1,
        CameraMoveLeft = 1 << 2,
        CameraMoveRight = 1 << 3,
        CameraZoom = 1 << 4,
        CameraToggleControl = 1 << 5,
        ChangeGizmoMode = 1 << 6,
        QuitApplication = 1 << 7,
    };

    enum class CameraMovement_
    {

    };
}
