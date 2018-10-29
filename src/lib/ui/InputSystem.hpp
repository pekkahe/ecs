#pragma once

#include <component/System.hpp>
#include <core/Defines.hpp>
#include <ui/InputListener.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class InputSystem : public System, public IWindowEventListener
    {
    public:
        InputSystem(Database& db, std::shared_ptr<Window> window);

        void update(const Scene& scene) override;

        void onKeyInput(Window& window, const InputEvent& input) override;
        void onMouseButton(Window& window, const InputEvent& input) override;
        void onMouseCursor(Window& window, double2 position) override;

    private:
        TableRef<InputListener> m_inputListenerTable;
    };
}