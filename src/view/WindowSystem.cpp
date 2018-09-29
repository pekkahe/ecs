#include <Precompiled.hpp>
#include <view/WindowSystem.hpp>
#include <view/Window.hpp>

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace eng;

namespace
{
	void onGlfwError(int error, const char* description)
	{
		SHOE_LOG_ERROR("%s [GLFW #%d]", description, error);
	}
}

WindowSystem::WindowSystem() 
{
	glfwSetErrorCallback(onGlfwError);

	if (!glfwInit())
	{
		throw std::runtime_error("Error: Failed to initialize GLFW.");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//const char* glsl_version = "#version 330 core"; // core -> es
	ImGui_ImplOpenGL3_Init(NULL); // Use default
	//auto io = ImGui::GetIO();
}

WindowSystem::~WindowSystem()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	m_windows.clear();

	glfwTerminate();
}

std::shared_ptr<Window> WindowSystem::createWindow(int width, int height, const std::string& title)
{
	m_windows.emplace_back(std::make_shared<Window>(width, height, title));

	return m_windows.back();
}

std::shared_ptr<Window> WindowSystem::mainWindow() const
{
	return m_windows.empty() ? nullptr : *m_windows.begin();
}
