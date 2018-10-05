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
        // Compute a view matrix from specific position.
        static mat4 viewMatrix(const Camera& camera, vec3 position);
        // Compute a perspective projection matrix.
        static mat4 projectionMatrix(const Camera& camera);

    public:
        Camera();

        // Recompute axis using given front vector.
        void align(vec3 front);
        // Modify field of view by given offset.
        void zoom(float offset);
    };
}

