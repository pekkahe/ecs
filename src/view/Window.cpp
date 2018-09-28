#include <Precompiled.hpp>
#include <view/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace eng;

Window::Window(
	GLFWwindow* glfwWindow) :
	m_glfwWindow(glfwWindow)
{
	glfwSetWindowUserPointer(m_glfwWindow, this);

	glfwSetKeyCallback(m_glfwWindow, onKeyInput);
	glfwSetCursorPosCallback(m_glfwWindow, onMouseCursor);
	glfwSetScrollCallback(m_glfwWindow, onMouseScroll);
	glfwSetFramebufferSizeCallback(m_glfwWindow, onFramebufferSizeCallback);
	glfwSetInputMode(m_glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Window::~Window()
{
	glfwSetWindowUserPointer(m_glfwWindow, nullptr);
	glfwDestroyWindow(m_glfwWindow);
}

int2 Window::size() const
{
	int2 size {};
	glfwGetWindowSize(m_glfwWindow, &size.x, &size.y);
	return size;
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_glfwWindow);
}

void Window::pollEvents()
{
	glfwPollEvents();
}

void Window::swapBuffers()
{
	glfwSwapBuffers(m_glfwWindow);
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

	std::cout << "Key press: " << key << std::endl;

	auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	for (auto& l : w->m_eventListeners)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS ||
			glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			l->onKeyPress(key);
		}
	}
}

void Window::onMouseCursor(GLFWwindow* window, double xpos, double ypos)
{
	auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	for (auto& l : w->m_eventListeners)
	{
		l->onMouseCursor(double2 { xpos, ypos });
	}
}

void Window::onMouseScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	for (auto& l : w->m_eventListeners)
	{
		l->onMouseScroll(double2 { xoffset, yoffset });
	}
}

void Window::onFramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	auto w = static_cast<Window*>(glfwGetWindowUserPointer(window));

	for (auto& l : w->m_eventListeners)
	{
		l->onWindowResize(int2 { width, height });
	}
}
