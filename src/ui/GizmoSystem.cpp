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
    if (!m_gizmoOperationChanged)
    {
        return;
    }
    m_gizmoOperationChanged = false;

    m_gizmoTable.forEach([&](EntityId id, Gizmo& gizmo) 
    {
        gizmo.operation = m_gizmoOperation;

        markUpdated(id);
    });
}

void GizmoSystem::onKeyInput(Window&, const InputEvent& input)
{
    if (input.key == GLFW_KEY_SPACE && input.action == GLFW_PRESS)
    {
        auto nextOperation = [&]()
        {
            int numberOfOperations = static_cast<int>(gizmoOperations.size());
            int indexOfNextOperation =
                m_gizmoOperation < numberOfOperations - 1 ?
                m_gizmoOperation + 1 : 0;

            return gizmoOperations[indexOfNextOperation];
        };

        m_gizmoOperation = nextOperation();
        m_gizmoOperationChanged = true;
    }
}