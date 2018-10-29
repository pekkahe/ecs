#pragma once

#include <component/System.hpp>
#include <core/Defines.hpp>
#include <scene/Hovered.hpp>
#include <scene/Selected.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class SelectionSystem : public System, public IWindowEventListener
    {
    public:
        SelectionSystem(Database& db, std::shared_ptr<Window> window);

        void update(const Scene& scene) override;

        void onKeyInput(Window& window, const InputEvent& input) override;
        void onMouseButton(Window& window, const InputEvent& input) override;
        void onMouseCursor(Window& window, double2 position) override;
        void onWindowResize(Window& window, int2 size) override;

    private:
        TableRef<Hovered> m_hoveredTable;
        TableRef<Selected> m_selectedTable;

        std::shared_ptr<Window> m_window;
    };
}