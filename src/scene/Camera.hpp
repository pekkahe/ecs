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

        vec3 front;
        vec3 right;
        vec3 up;
        mat4 view = mat4(1.0f);
        mat4 projection = mat4(1.0f);

    public:
        Camera();

        void zoom(float offset);
        void lookAt(vec3 from, vec3 target);
        void computeViewMatrix(vec3 position);
    };
}

