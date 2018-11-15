#include <Precompiled.hpp>
#include <scene/SelectionSystem.hpp>

#include <graphics/Mesh.hpp>
#include <graphics/Raycast.hpp>
#include <scene/Camera.hpp>
#include <scene/Scene.hpp>

#include <ImGuizmo.h>

using namespace eng;

SelectionSystem::SelectionSystem(
    Database& db) :
    m_hoveredTable(db.createTable<Hovered>()),
    m_selectedTable(db.createTable<Selected>())
{
}

void SelectionSystem::update(const Scene& scene)
{
    const auto& input = scene.window().frameInput();

    // Prevent selection changes when the cursor is
    // either captured or over the transform gizmo 
    if (input.cursorCaptured || ImGuizmo::IsOver())
    {
        return;
    }

    // Assign Hovered on mouse cursor move
    if (input.cursorMoved)
    {
        // Always clear Hovered on mouse move
        m_hoveredTable.clear();

        auto camera = query().find<Camera>();
        assert(camera != nullptr && "No camera in scene");

        // Cast ray from cursor screen position to all meshes
        Ray ray = camera->screenPointToRay(
            input.cursorPositionNormalized);

        auto closestId = InvalidId;
        auto closestDistance = std::numeric_limits<float>::max();

        query()
            .hasComponent<Mesh>()
            .execute([&](
                EntityId id,
                const Mesh& mesh)
        {
            float d = gfx::raycast(ray, mesh.obb);
            if (d > 0.f && d < closestDistance)
            {
                closestId = id;
                closestDistance = d;
            }
        });
        
        // Assign Hovered to closest hit
        if (closestId != InvalidId)
        {
            m_hoveredTable.assign(closestId, Hovered());
        }
    }

    // Assign Selected on mouse button press
    if (input.isButtonPressed(GLFW_MOUSE_BUTTON_1))
    {
        bool inToggleSelectionMode = input.isKeyDown(GLFW_KEY_LEFT_CONTROL) ||
                                     input.isKeyDown(GLFW_KEY_RIGHT_CONTROL);
        if (inToggleSelectionMode)
        {
            m_hoveredTable.forEach([&](EntityId id, Hovered&)
            {
                if (m_selectedTable.check(id))
                {
                    m_selectedTable.remove(id);
                }
                else
                { 
                    m_selectedTable.assign(id, Selected());
                }
            });
        }
        else
        {
            m_selectedTable.clear();
            m_hoveredTable.forEach([&](EntityId id, Hovered&)
            {
                m_selectedTable.assign(id, Selected());
            });
        }
    }
}
