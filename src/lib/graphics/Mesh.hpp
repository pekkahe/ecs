#pragma once

#include <component/IComponent.hpp>
#include <core/Defines.hpp>
#include <graphics/AABB.hpp>
#include <graphics/OBB.hpp>

namespace eng
{
    class Mesh : public IComponent
    {
    public:
        std::vector<vec3> vertices;
        std::vector<vec3> colors;
        std::vector<unsigned> indices;

        AABB aabb;
        OBB obb;

        unsigned int VAO = 0u;
        unsigned int VBOV = 0u; // vertices
        unsigned int VBOC = 0u; // colors
        unsigned int EBO = 0u;
    };
}
