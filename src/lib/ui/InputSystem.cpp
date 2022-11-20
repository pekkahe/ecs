#include <Precompiled.hpp>
#include <ui/InputSystem.hpp>

#include <editor/components/Selected.hpp>

using namespace eng;

InputSystem::InputSystem(Database& db, std::shared_ptr<Window> window) : 
    m_inputListenerTable(db.createTable<InputListener>())
{
}

void InputSystem::update(const Scene&)
{
    query()
        .hasComponent<Selected>()
        .hasComponent<InputListener>(m_inputListenerTable)
        .execute([&](
            EntityId,
            const Selected&,
            InputListener&)
    {

    });
}

void InputSystem::onKeyInput(Window&, const InputEvent&)
{
}

void InputSystem::onMouseButton(Window&, const InputEvent&)
{
}

void InputSystem::onMouseCursor(Window&, double2 /*position*/)
{
}
