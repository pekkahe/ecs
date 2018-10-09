#pragma once

#include <component/IComponent.hpp>
#include <core/Defines.hpp>

namespace eng
{
    class Camera : public IComponent
    {
    public:
        static const vec3 WorldUp;

        float fov = 45.0f;
        float aspectRatio = 1.0f;
        float nearPlane = 0.1f;
        float farPlane = 100.0f;

        // todo: these could be cached in a separate CameraMatrix component
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);
    };
}

