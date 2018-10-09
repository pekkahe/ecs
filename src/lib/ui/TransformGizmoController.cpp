#include <Precompiled.hpp>
#include <ui/TransformGizmoController.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

bool TransformGizmoController::update(TransformGizmo& gizmo)
{
    if (m_updated)
    {
        gizmo.operation = m_operation;
    }

    return std::exchange(m_updated, false);
}

void TransformGizmoController::onKeyInput(Window &, const InputEvent & input)
{
    static constexpr std::array<ImGuizmo::OPERATION, 4> operations =
    {
        ImGuizmo::OPERATION::TRANSLATE,
        ImGuizmo::OPERATION::ROTATE,
        ImGuizmo::OPERATION::SCALE
    };
    static constexpr size_t operationsCount = operations.size();

    if (input.key == GLFW_KEY_SPACE && input.action == GLFW_PRESS)
    {
        auto nextOperation = [&](const ImGuizmo::OPERATION& current)
        {
            size_t nextOperationIndex = current < (operationsCount - 1) ? current + 1 : 0;

            return operations[nextOperationIndex];
        };

        m_operation = nextOperation(m_operation);
        m_updated = true;
    }
}
