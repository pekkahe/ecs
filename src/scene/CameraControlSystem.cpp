#include <Precompiled.hpp>
#include <scene/CameraControlSystem.hpp>

#include <scene/Camera.hpp>
#include <scene/Scene.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

CameraControlSystem::CameraControlSystem(
    Database& db) :
    m_cameraControlTable(db.createTable<CameraControl>())
{
    // todo: pass window size as ctor argument?
    m_lastX = static_cast<double>(640) / 2;
    m_lastY = static_cast<double>(480) / 2;
}

CameraControlSystem::~CameraControlSystem()
{
}

void CameraControlSystem::update(const Scene&)
{
    if (!m_cameraControlChanged)
    {
        return;
    }
    m_cameraControlChanged = false;

    m_cameraControlTable.forEach([&](EntityId id, CameraControl& control)
    {
        control = m_cameraControl;

        markUpdated(id);
    });
}

void CameraControlSystem::onKeyInput(Window&, const InputEvent& input)
{
    auto updateMovement = [&](int ifKey, CameraMovement movement)
    {
        if (input.key == ifKey)
        {
            if (input.action != GLFW_RELEASE)
            {
                m_cameraControl.movement |= movement;
            }
            else
            {
                m_cameraControl.movement &= ~movement;
            }
        }
    };

    updateMovement(GLFW_KEY_W, CameraMovement::Forward);
    updateMovement(GLFW_KEY_S, CameraMovement::Backward);
    updateMovement(GLFW_KEY_A, CameraMovement::Left);
    updateMovement(GLFW_KEY_D, CameraMovement::Right);

    m_cameraControlChanged = true;
}

void CameraControlSystem::onMouseButton(Window& window, const InputEvent& input)
{
    if (input.key == GLFW_MOUSE_BUTTON_RIGHT)
    {
        m_enabled = input.action == GLFW_PRESS;
        m_enabledCursorDelay = m_enabled ? 1 : 0;

        window.captureMouseCursor(m_enabled);
    }
}

void CameraControlSystem::onMouseCursor(Window&, double2 screenPosition)
{
    if (m_firstMouse)
    {
        m_lastX = screenPosition.x;
        m_lastY = screenPosition.y;
        m_firstMouse = false;
    }

    // Reversed y-coordinates since range is from bottom to top
    double xoffset = screenPosition.x - m_lastX;
    double yoffset = m_lastY - screenPosition.y;

    // Store screen position always to keep offset calculation up-to-date
    m_lastX = screenPosition.x;
    m_lastY = screenPosition.y;

    if (!m_enabled)
    {
        return;
    }

    // When toggling mouse cursor capture, GLFW does its own saving and restoring of
    // the cursor position. The position appears to jump incorrectly in some cases right
    // after mouse capture is enabled. To prevent this from wildly changing our camera
    // rotation, we ignore the one inaccurate offset calculation after the change.

    if (m_enabledCursorDelay > 0)
    {
        m_enabledCursorDelay--;
        return;
    }

    xoffset *= m_cameraControl.sensitivity;
    yoffset *= m_cameraControl.sensitivity;

    m_cameraControl.yaw   += static_cast<float>(xoffset);
    m_cameraControl.pitch += static_cast<float>(yoffset);

    math::clamp(m_cameraControl.pitch, -89.0f, 89.0f);

    m_cameraControlChanged = true;
}

void CameraControlSystem::onMouseScroll(Window&, double2 offset)
{
    m_cameraControl.zoom = static_cast<float>(offset.y);

    m_cameraControlChanged = true;
}
