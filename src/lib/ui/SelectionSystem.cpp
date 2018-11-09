#include <Precompiled.hpp>
#include <ui/SelectionSystem.hpp>

#include <graphics/Mesh.hpp>
#include <graphics/Raycast.hpp>
#include <scene/Camera.hpp>
#include <scene/Transform.hpp>
#include <scene/TransformGizmo.hpp>

#include <ImGuizmo.h>

using namespace eng;

SelectionSystem::SelectionSystem(
    Database& db,
    std::shared_ptr<Window> window) :
    m_hoveredTable(db.createTable<Hovered>()),
    m_selectedTable(db.createTable<Selected>()),
    m_window(std::move(window))
{
}

void SelectionSystem::update(const Scene&)
{
    const auto& input = m_window->input();

    if (input.cursorCaptured)
    {
        return;
    }

    if (input.cursorMoved)
    {
        m_hoveredTable.clear();

        query()
            .hasComponent<Camera>()
            .execute([&](
                EntityId id,
                const Camera& camera)
        {
            Ray ray = camera.screenPointToRay(
                input.cursorPositionNormalized);

            query()
                .hasComponent<Mesh>()
                .execute([&](
                    EntityId id,
                    const Mesh& mesh)
            {
                // TODO: Hover closest hit only

                if (gfx::raycast(ray, mesh.obb) > 0)
                {
                    m_hoveredTable.assign(id, Hovered());
                }
            });
        });
    }

    if (input.leftButtonPress && !ImGuizmo::IsOver())
    {
        m_selectedTable.clear();
        
        m_hoveredTable.forEach([&](EntityId id, Hovered&) 
        {
            m_selectedTable.assign(id, Selected());
        });

        // If we have selected meshes, select the transform gizmo
        // as well to activate it
        if (!m_selectedTable.empty())
        { 
            query()
                .hasComponent<TransformGizmo>()
                .executeIds([&](EntityId id)
            {
                m_selectedTable.assign(id, Selected());
            });
        }
    }
}
