#pragma once

#include <core/Defines.hpp>

struct GLFWwindow;

namespace eng
{
    class IWindowEventListener;
    class Window : public trait::non_copyable_nor_movable
    {
    public:
        using WindowResizeCallback = std::function<void(int2)>;

    public:
        Window(int width, int height, const std::string& title);
        ~Window();

        // The height and width of this window.
        int2 size() const;
        
        // Poll and handle events (input, window resizing, etc.)
        // Returns false if window should be closed.
        bool pollEvents();

        // Swap the front and back buffers of this window.
        void swapBuffers();

        void captureMouseCursor(bool capture);

        double2 cursorPosition() const;

        // Add an input and message event listener to this window.
        void addEventListener(std::shared_ptr<IWindowEventListener> listener);

        void onWindowResize(WindowResizeCallback callback);

    private:
        static void onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void onMouseButton(GLFWwindow* window, int button, int action, int mods);
        static void onMouseCursor(GLFWwindow* window, double xpos, double ypos);
        static void onMouseScroll(GLFWwindow* window, double xoffset, double yoffset);
        static void onFramebufferSizeCallback(GLFWwindow* window, int width, int height);

    private:
        GLFWwindow* m_window = nullptr;

        //std::shared_ptr<IWindowEventListener> m_selfListener;
        std::vector<WindowResizeCallback> m_windowResizeCallbacks;
        std::vector<std::shared_ptr<IWindowEventListener>> m_eventListeners;
    };

    struct InputEvent
    {
        int key = 0;
        int action = 0;
        int mods = 0;
    };

    // Window input and message event listener.
    // New events are only received at the start of each frame.
    class IWindowEventListener
    {
    public:
        // todo: replace direct input callbacks with processed 'KeyBindings'

        virtual void onKeyInput(Window& window, const InputEvent& input) {}
        virtual void onMouseButton(Window& window, const InputEvent& input) {}
        virtual void onMouseCursor(Window& window, double2 position) {}
        virtual void onMouseScroll(Window& window, double2 offset) {}
        virtual void onWindowResize(Window& window, int2 size) {}
    };
}
