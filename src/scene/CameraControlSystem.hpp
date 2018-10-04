#pragma once

#include <component/System.hpp>
#include <core/Defines.hpp>
#include <scene/CameraControl.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class CameraControlSystem : public System, public IWindowEventListener
    {
    public:
        ADD_COMPONENT_FUNCTION(CameraControl, m_cameraControlTable);

    public:
        CameraControlSystem(Database& db);
        ~CameraControlSystem();

        void update(const Scene&) override;

    public:
        void onKeyInput(Window& window, const InputEvent& input) override;
        void onMouseButton(Window& window, const InputEvent& input) override;
        void onMouseCursor(Window& window, double2 position) override;
        void onMouseScroll(Window& window, double2 offset) override;

    public:
        bool m_firstMouse = true;
        bool m_enabled = false;
        int  m_enabledCursorDelay = 0;

        double m_lastX = 0.0f;
        double m_lastY = 0.0f;

        TableRef<CameraControl> m_cameraControlTable;

        // Local control component, copied to table each update
        CameraControl m_cameraControl;
    };
}
