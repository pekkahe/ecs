#include <Precompiled.hpp>
#include <scene/EditorSystem.hpp>

#include <scene/Scene.hpp>
#include <ui/Window.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

EditorSystem::EditorSystem(
    Database& db) :
    m_transformGizmoTable(db.createTable<TransformGizmo>())
{
}

EditorSystem::~EditorSystem()
{
}

void EditorSystem::update(const Scene& scene)
{
    const auto& input = scene.window().frameInput();

    // Cycle gizmo operation
    if (input.isKeyPressed(GLFW_KEY_SPACE))
    {
        static constexpr std::array<ImGuizmo::OPERATION, 4> operations =
        {
            ImGuizmo::OPERATION::TRANSLATE,
            ImGuizmo::OPERATION::ROTATE,
            ImGuizmo::OPERATION::SCALE
        };
        static constexpr size_t operationsCount = operations.size();

        auto nextOperation = [&](const ImGuizmo::OPERATION& current)
        {
            size_t nextOperationIndex = current < (operationsCount - 1) ? current + 1 : 0;

            return operations[nextOperationIndex];
        };

        m_transformGizmoTable.forEach([&](EntityId, TransformGizmo& gizmo) 
        {
            gizmo.operation = nextOperation(gizmo.operation);
        });
    }

    // Toggle gizmo mode
    if (input.isKeyPressed(GLFW_KEY_G))
    {
        m_transformGizmoTable.forEach([&](EntityId, TransformGizmo& gizmo)
        {
            gizmo.mode = gizmo.mode == ImGuizmo::MODE::LOCAL ?
                ImGuizmo::MODE::WORLD :
                ImGuizmo::MODE::LOCAL;
        });
    }

    // Delete selected entities
    if (input.isKeyPressed(GLFW_KEY_DELETE))
    {
        query()
            .hasComponent<Selected>()
            .executeIds([&](EntityId id) 
        {
            markDeleted(id);
        });
    }
}
