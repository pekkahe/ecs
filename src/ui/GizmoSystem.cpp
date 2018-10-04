#include <Precompiled.hpp>
#include <ui/GizmoSystem.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

namespace
{
    static constexpr std::array<ImGuizmo::OPERATION, 4> gizmoOperations =
    {
        ImGuizmo::OPERATION::TRANSLATE,
        ImGuizmo::OPERATION::ROTATE,
        ImGuizmo::OPERATION::SCALE
    };
}

GizmoSystem::GizmoSystem(Database& db) :
    m_gizmoTable(db.createTable<Gizmo>())
{
}

GizmoSystem::~GizmoSystem()
{
}

void GizmoSystem::update(const Scene&)
{
    query()
        .hasComponent(m_gizmoTable)
        .execute([&](EntityId id, Gizmo& gizmo)
    {
        gizmo.operation = m_gizmoOperation;
    });
}

void GizmoSystem::onKeyInput(Window&, const InputEvent& input)
{
    if (input.key == GLFW_KEY_SPACE && input.action == GLFW_PRESS)
    {
        int size = static_cast<int>(gizmoOperations.size());

        m_gizmoOperation = gizmoOperations[
            m_gizmoOperation < size - 1 ?
                m_gizmoOperation + 1 : 0];
    }
}