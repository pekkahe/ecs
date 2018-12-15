#pragma once

#include <component/IComponent.hpp>
#include <core/Defines.hpp>

namespace eng
{
    class Transform : public IComponent
    {
    public:
        vec3 position = vec3(0.0f, 0.0f, 0.0f);
        qua	 rotation = qua(1.0f, 0.0f, 0.0f, 0.0f);
        vec3 scale    = vec3(1.0f, 1.0f, 1.0f);

    public:
        Transform() = default;
        Transform(vec3 pos) : position(pos) {}
        Transform(vec3 pos, qua rot) : position(pos), rotation(rot) {}
        Transform(vec3 pos, qua rot, vec3 scale) : position(pos), rotation(rot), scale(scale) {}

        mat4 modelMatrix() const
        {
            mat4 translate = glm::translate(mat4(1.0f), position);
            mat4 rotate = glm::mat4_cast(rotation);
            mat4 scale_ = glm::scale(mat4(1.0f), scale);

            return translate * rotate * scale_;
        }
    };
}