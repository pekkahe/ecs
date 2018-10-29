#pragma once

#include <core/Datatypes.hpp>

namespace eng
{
    // Axis-aligned bounding box.
    class BoundingBox
    {
    public:
        BoundingBox();

        void expand(const vec3& point);
        void clear();
        
        bool valid() const;

        const vec3& min() const { return m_min; }
        const vec3& max() const { return m_max; }
        vec3 center() const;

    private:
        vec3 m_min;
        vec3 m_max;
    };
}
