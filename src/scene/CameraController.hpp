#pragma once

#include <core/Core.hpp>
#include <scene/CameraControl.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class CameraController : public IWindowEventListener
    {
    public:
        CameraController(int2 windowSize);

        bool update(CameraControl& control);

        void onKeyInput(Window& window, const InputEvent& input) override;
        void onMouseButton(Window& window, const InputEvent& input) override;
        void onMouseCursor(Window& window, double2 position) override;
        void onMouseScroll(Window& window, double2 offset) override;

    private:
        bool m_firstMouse = true;
        bool m_updated = false;
        bool m_captured = false;
        int  m_capturedCursorDelay = 0;

        CameraMovement m_movement = CameraMovement::None;

        double m_lastX = 0.0f;
        double m_lastY = 0.0f;
        float m_offsetX = 0.0f;
        float m_offsetY = 0.0f;
        float m_zoom = 0.0f;
    };
}
