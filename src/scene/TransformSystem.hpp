#pragma once

#include <component/System.hpp>

#include <scene/Transform.hpp>

namespace eng
{
    class TransformSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Transform, m_transformTable);

    public:
        TransformSystem(Database& db);
        ~TransformSystem();

        void update(const Scene& scene) override;

    private:
        TableRef<Transform> m_transformTable;
    };
}