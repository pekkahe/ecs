#pragma once

#include <core/Defines.hpp>

#include <bitset>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace eng
{ 
    // Frame specific cached mouse and keyboard input state.
    class FrameInput
    {
    public:
        // Mouse cursor position in pixel coordinates.
        double2 cursorPosition = { 0.0f, 0.0f };
        // Mouse cursor position in normalized device coordinates within range [-1, 1].
        double2 cursorPositionNormalized = { 0.0f, 0.0f };

        // Whether mouse cursor moved this frame.
        bool cursorMoved = false;
        // Whether mouse cursor is captured by the window.
        bool cursorCaptured = false;

    public:
        // Maintain input state cache. Should be called each frame before setting new input state.
        void beginFrame();

        // Set key state for a GLFW key code and action.
        void setKey(int key, int action);
        // Return whether the specified GLFW key was pressed this frame.
        bool isKeyPressed(int key) const;
        // Return whether the specified GLFW key was released this frame.
        bool isKeyReleased(int key) const;
        // Return whether the specified GLFW key is currently pressed down.
        bool isKeyDown(int key) const;

        // Set button state for a GLFW button code and action.
        void setButton(int button, int action);
        // Return whether the specified GLFW button was pressed this frame.
        bool isButtonPressed(int button) const;
        // Return whether the specified GLFW button was released this frame.
        bool isButtonReleased(int button) const;
        // Return whether the specified GLFW button is currently pressed down.
        bool isButtonDown(int button) const;

    private:
        struct KeyCodes
        {
            std::bitset<GLFW_KEY_LAST + 1> released;
            std::bitset<GLFW_KEY_LAST + 1> pressed;
            std::bitset<GLFW_KEY_LAST + 1> repeated;
        };

        KeyCodes m_keys;
        KeyCodes m_buttons;
    };
}