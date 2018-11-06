#include <Precompiled.hpp>
#include <ui/SelectionSystem.hpp>

#include <graphics/Mesh.hpp>
#include <graphics/Raycast.hpp>
#include <scene/Camera.hpp>
#include <scene/Transform.hpp>
#include <ui/ImGui.hpp>

#include <GLFW/glfw3.h>

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
    if (!m_window->isMouseCursorMoved() || m_window->isMouseCursorCaptured())
    {
        return;
    }

    double2 cursorPos = m_window->mouseCursorNormalizedPosition();

    auto camera = query().find<Camera>();
    assert(camera != nullptr && "No camera in scene");

    gfx::Ray ray = gfx::cursorPosToWorldRay(cursorPos, *camera);

    //SHOE_LOG("\n "
    //    "Cursor (%f %f) \n "
    //    "Ray ori (%f %f %f) \n "
    //    "Ray dir (%f %f %f) \n ",
    //    cursorPos.x, cursorPos.y, 
    //    ray.origin.x, ray.origin.y, ray.origin.z,
    //    ray.direction.x, ray.direction.y, ray.direction.z);

    m_hoveredTable.clear();

    query()
        .hasComponent<Mesh>()
        .hasComponent<Transform>()
        .execute([&](
            EntityId id,
            const Mesh& mesh,
            const Transform& transform)
    {
        if (gfx::raycast(ray, mesh.obb) > 0.f)
        {
            m_hoveredTable.assign(id, Hovered());
        }

        //auto model = transform.modelMatrix();
        //float distance = 0.0f;
        //if (gfx::raycastObb(
        //    ray,
        //    mesh.aabb, 
        //    model,
        //    distance))
        //{
        //    m_hoveredTable.assign(id, Hovered());
        //}
    });
}

void SelectionSystem::onKeyInput(Window& window, const InputEvent& input)
{
}

void SelectionSystem::onMouseButton(Window& window, const InputEvent& input)
{
    if (input.key == GLFW_MOUSE_BUTTON_RIGHT && input.action == GLFW_PRESS)
    {
    }
}

void SelectionSystem::onMouseCursor(Window& window, double2 position)
{
}

void SelectionSystem::onWindowResize(Window & window, int2 size)
{
}
