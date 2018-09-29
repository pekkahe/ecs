#include <Precompiled.hpp>

#include <component/Query.hpp>
#include <core/Engine.hpp>
#include <scene/Scene.hpp>
#include <scene/Camera.hpp>
#include <scene/CameraController.hpp>

#include <graphics/Renderer.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

using namespace eng;
using namespace eng::gfx;

namespace imgui
{
    void startFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void endFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

Engine::Engine()
{
}

Engine::~Engine()
{
}

void Engine::execute()
{
    m_running = true;
    //gfx::Renderer oldRenderer;

    auto window = m_windowSystem.createWindow(640, 480, "Shoe");
    auto scene = m_sceneSystem.createScene();

    scene->createTestMesh();

    auto cameraController = std::make_shared<CameraController>(scene->camera(), window);

    window->addListener(cameraController);

    while (window->pollEvents())
    {
        imgui::startFrame();

        bool open = true;
        ImGui::ShowDemoWindow(&open);

        // Logic thread?
        scene->update();
        cameraController->update();

        // Render thread?
        scene->renderer().beginFrame();
        scene->renderer().render(*scene);
        scene->renderer().endFrame();
        //oldRenderer.drawRectangle();

        imgui::endFrame();
        window->swapBuffers();
        
        Time::update(glfwGetTime());
    }
}

void Engine::terminate()
{
    m_running = false;
}
