#include <Precompiled.hpp>
#include <ui/InputSystem.hpp>

#include <editor/Selected.hpp>

using namespace eng;

InputSystem::InputSystem(Database& db, std::shared_ptr<Window> window) : 
    m_inputListenerTable(db.createTable<InputListener>())
{
}

void InputSystem::update(const Scene & scene)
{
    query()
        .hasComponent<Selected>()
        .hasComponent<InputListener>(m_inputListenerTable)
        .execute([&](
            EntityId,
            const Selected&,
            InputListener& listener)
    {

    });
}

void InputSystem::onKeyInput(Window& window, const InputEvent& input)
{
}

void InputSystem::onMouseButton(Window& window, const InputEvent& input)
{
}

void InputSystem::onMouseCursor(Window& window, double2 position)
{
}
