#include <Precompiled.hpp>
#include <view/WindowSystem.hpp>
#include <view/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace eng;

namespace
{
	void onGlfwError(int error, const char* description)
	{
		std::cerr << "Error: " << description << std::endl;
	}
}

WindowSystem::WindowSystem()
{
	glfwSetErrorCallback(onGlfwError);
	if (!glfwInit())
	{
		throw std::runtime_error("Error: Failed to initialize GLFW.");
	}
}

WindowSystem::~WindowSystem()
{
	glfwTerminate();
}

std::shared_ptr<Window> WindowSystem::createWindow(int width, int height, const std::string& title)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!window)
	{
		throw std::runtime_error("Error: Window or OpenGL context creation failed.");
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
	{
		throw std::runtime_error("Error: Failed to initialize GLAD.");
	}

	glfwSwapInterval(1);

	m_windows.emplace_back(std::make_shared<Window>(window));
	return m_windows.back();
}

std::shared_ptr<Window> WindowSystem::mainWindow() const
{
	return m_windows.empty() ? nullptr : *m_windows.begin();
}
