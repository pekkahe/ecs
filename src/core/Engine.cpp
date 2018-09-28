#include <Precompiled.hpp>

#include <component/Query.hpp>
#include <core/Engine.hpp>
#include <scene/Scene.hpp>
#include <scene/Camera.hpp>
#include <scene/CameraController.hpp>

#include <graphics/Renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace eng;
using namespace eng::gfx;

Engine::Engine()
{
	m_windowSystem.createWindow(640, 480, "Main Window");
}

Engine::~Engine()
{
}

void Engine::execute()
{
	m_running = true;

	Time time;
	//gfx::Renderer oldRenderer;

	auto window = m_windowSystem.mainWindow();
	auto scene = m_sceneSystem.createScene();

	scene->createTestMesh();

	auto cameraController = std::make_shared<CameraController>(scene->camera(), window->size());
	window->addListener(cameraController);

	while (!window->shouldClose())
	{
		window->pollEvents();

		// Logic thread?
		scene->update();
		
		// Render thread?
		scene->renderer().beginFrame();
		scene->renderer().render(*scene);
		scene->renderer().endFrame();

		//oldRenderer.drawRectangle();

		window->swapBuffers();

		time.update(static_cast<float>(glfwGetTime()));
	}
}

void Engine::terminate()
{
	m_running = false;
}
