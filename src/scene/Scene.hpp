#pragma once

#include <component/Database.hpp>
#include <component/Query.hpp>

#include <graphics/RenderSystem.hpp>

#include <scene/CameraSystem.hpp>
#include <scene/TransformSystem.hpp>

namespace eng
{
    class Scene : public trait::non_copyable
    {
    public:
        Scene(std::shared_ptr<Window> window);
        ~Scene();
        Scene(Scene&&) = default;
        Scene& operator=(Scene&&) = default;

        void createTestEntities();

        void registerSystem(ISystem& system);
        void update();

        EntityId createEntity();

        RenderSystem& renderer() { return m_renderSystem; }

        // Receive read-only access to scene database. Only 
        // subsystems are allowed to modify database content.
        const Database& database() const { return m_database; }

    private:
        Database m_database;

        std::vector<ISystem*> m_systems;

        TransformSystem m_transformSystem;
        RenderSystem m_renderSystem;
        CameraSystem m_cameraSystem;
    };
}
