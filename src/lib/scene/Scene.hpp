#pragma once

#include <component/Database.hpp>
#include <graphics/RenderSystem.hpp>
#include <scene/CameraSystem.hpp>
#include <scene/TransformSystem.hpp>
#include <ui/SelectionSystem.hpp>

namespace eng
{
    class Scene : public trait::non_copyable
    {
    public:
        Scene(std::shared_ptr<Window> window);
        ~Scene();
        Scene(Scene&&) = default;
        Scene& operator=(Scene&&) = default;

        void registerSystem(ISystem& system);
        void update();

        // TODO: entity creation, move into factory class?
        EntityId createEntity();
        EntityId createCamera();
        EntityId createCube(vec3 position);
        EntityId createGizmo();

        RenderSystem& renderer() { return m_renderSystem; }

        // Read-only access to scene database. Only systems are
        // allowed to modify database content for their own tables.
        const Database& database() const { return m_database; }

    private:
        Database m_database;
        std::shared_ptr<Window> m_window;

        std::vector<ISystem*> m_systems;

        TransformSystem m_transformSystem;
        RenderSystem m_renderSystem;
        CameraSystem m_cameraSystem;
        SelectionSystem m_selectionSystem;
    };
}
