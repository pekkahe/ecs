#pragma once

#include <component/IComponent.hpp>

#include <core/Defines.hpp>

namespace eng
{
    class Mesh : public IComponent
    {
    public:
        std::vector<vec3> vertices;
        std::vector<unsigned> indices;

        unsigned int VAO = 0u;
        unsigned int VBO = 0u;
        unsigned int EBO = 0u;
    };
}
