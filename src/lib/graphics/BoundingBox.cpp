#include <Precompiled.hpp>
#include <graphics/BoundingBox.hpp>

using namespace eng;

BoundingBox::BoundingBox()
{
    clear();
}

void BoundingBox::expand(const vec3& point)
{
    if (m_min.x > point.x) m_min.x = point.x;
    if (m_min.y > point.y) m_min.y = point.y;
    if (m_min.z > point.z) m_min.z = point.z;

    if (m_max.x < point.x) m_max.x = point.x;
    if (m_max.y < point.y) m_max.y = point.y;
    if (m_max.z < point.z) m_max.z = point.z;
}

void BoundingBox::clear()
{
    m_min = vec3(std::numeric_limits<float>::max());
    m_max = vec3(std::numeric_limits<float>::min());
}

bool BoundingBox::valid() const
{
    return m_min.x <= m_max.x &&
           m_min.y <= m_max.y &&
           m_min.z <= m_max.z;
}

vec3 BoundingBox::center() const
{
    return vec3(
        m_min.x + ((m_max.x - m_min.x) / 2),
        m_min.y + ((m_max.y - m_min.y) / 2),
        m_min.z + ((m_max.z - m_min.z) / 2));
}