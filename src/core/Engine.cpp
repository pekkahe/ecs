#include <Precompiled.hpp>
#include <core/Engine.hpp>

#include <scene/Scene.hpp>
#include <ui/ImGui.hpp>

using namespace eng;
using namespace eng::gfx;

namespace
{
    void onGlfwError(int error, const char* description)
    {
        SHOE_LOG_ERROR("%s [GLFW #%d]", description, error);
    }
}

Engine::Engine()
{
    glfwSetErrorCallback(onGlfwError);

    if (!glfwInit())
    {
        throw std::runtime_error("Error: Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    imgui::init();
}

Engine::~Engine()
{
    imgui::deinit();

    glfwTerminate();
}

void Engine::execute()
{
    auto window = std::make_shared<Window>(640, 480, "Shoe");
    auto scene = std::make_shared<Scene>(window);

    scene->createCube(vec3(-1.5f, 0.0f, -3.0f));
    scene->createCube(vec3(0.0f,  0.0f, -3.0f));
    scene->createCube(vec3(1.5f,  0.0f, -3.0f));

    while (window->pollEvents() && !m_terminate)
    {
        imgui::beginFrame();

        // TODO: logic thread
        scene->update();

        // TODO: render thread
        scene->renderer().beginFrame();
        scene->renderer().render();
        scene->renderer().endFrame();

        imgui::endFrame();
        window->swapBuffers();

        Time::endFrame();
    }
}

void Engine::terminate()
{
    m_terminate = true;
}
