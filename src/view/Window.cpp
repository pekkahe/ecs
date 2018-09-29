#include <Precompiled.hpp>
#include <view/Window.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace eng;

namespace
{
    inline static Window* getUserWindow(GLFWwindow* window)
    {
        return static_cast<Window*>(glfwGetWindowUserPointer(window));
    }
}

Window::Window(int width, int height, const std::string& title)
{
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!m_window)
    {
        throw std::runtime_error("Error: Window or OpenGL context creation failed.");
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        throw std::runtime_error("Error: Failed to initialize OpenGL loader GLAD.");
    }

    glfwSetWindowUserPointer(m_window, this);
    glfwSetKeyCallback(m_window, onKeyInput);
    glfwSetMouseButtonCallback(m_window, onMouseButton);
    glfwSetCursorPosCallback(m_window, onMouseCursor);
    glfwSetScrollCallback(m_window, onMouseScroll);
    glfwSetFramebufferSizeCallback(m_window, onFramebufferSizeCallback);

    ImGui_ImplGlfw_InitForOpenGL(m_window, false); // 'true' steals input
    
    ImGui::StyleColorsDark();
}

Window::~Window()
{
    glfwSetWindowUserPointer(m_window, nullptr);
    glfwDestroyWindow(m_window);
}

int2 Window::size() const
{
    int2 size {};
    glfwGetWindowSize(m_window, &size.x, &size.y);
    return size;
}

bool Window::pollEvents()
{
    if (glfwWindowShouldClose(m_window))
    {
        return false;
    }

    glfwPollEvents();
    return true;
}

void Window::swapBuffers()
{
    glfwMakeContextCurrent(m_window);
    glfwSwapBuffers(m_window);
}

void Window::captureMouseCursor(bool capture)
{
    glfwSetInputMode(m_window, GLFW_CURSOR, capture ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

double2 Window::cursorPosition() const
{
    double2 pos;
    glfwGetCursorPos(m_window, &pos.x, &pos.y);
    return pos;
}

void Window::addListener(std::shared_ptr<EventListener> listener)
{
    m_eventListeners.emplace_back(std::move(listener));
}

void Window::onKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        return;
    }

    auto w = getUserWindow(window);

    for (auto& l : w->m_eventListeners)
    {
        l->onKeyInput(key, action, mods);
    }
}

void Window::onMouseButton(GLFWwindow* window, int button, int action, int mods)
{
    auto w = getUserWindow(window);

    for (auto& l : w->m_eventListeners)
    {
        l->onMouseButton(button, action, mods);
    }
}

void Window::onMouseCursor(GLFWwindow* window, double xpos, double ypos)
{
    auto w = getUserWindow(window);

    for (auto& l : w->m_eventListeners)
    {
        l->onMouseCursor(double2 { xpos, ypos });
    }
}

void Window::onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
    auto w = getUserWindow(window);

    for (auto& l : w->m_eventListeners)
    {
        l->onMouseScroll(double2 { xoffset, yoffset });
    }
}

void Window::onFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

    auto w = getUserWindow(window);

    for (auto& l : w->m_eventListeners)
    {
        l->onWindowResize(int2 { width, height });
    }
}
