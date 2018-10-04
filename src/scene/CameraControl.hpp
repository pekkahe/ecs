#pragma once

#include <component/IComponent.hpp>

#include <core/Defines.hpp>

namespace eng
{
    ENUM_FLAGS(CameraMovement)
    {
        None = 0,
        Forward = 1 << 0,
        Backward = 1 << 1,
        Left = 1 << 2,
        Right = 1 << 3
    };

    class CameraControl : public IComponent
    {
    public:
        float speed = 2.0f;
        float sensitivity = 0.05f;

        float zoom = 0.0f;
        CameraMovement movement = CameraMovement::None;

        float yaw = -90.0f; // Default front is -z
        float pitch = 0.0f;

        vec3 front = vec3(0.0f, 0.0f, 0.0f);
    };
}