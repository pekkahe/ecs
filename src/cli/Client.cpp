#include <Precompiled.hpp>
#include <Client.hpp>

#include <scene/Scene.hpp>
#include <ui/ImGui.hpp>

namespace client
{
    
void onGlfwError(int error, const char* description)
{
    SHOE_LOG_ERROR("%s [GLFW #%d]", description, error);
}

void init()
{
    glfwSetErrorCallback(onGlfwError);

    if (!glfwInit())
    {
        assert(false && "Failed to initialize GLFW.");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ecs::imgui::init();
}

void deinit()
{
    ecs::imgui::deinit();

    glfwTerminate();
}

void run(std::shared_ptr<ecs::Window> window, std::shared_ptr<ecs::Scene> scene)
{
    while (window->pollEvents())
    {
        ecs::imgui::beginFrame();

        scene->update();
        
        scene->renderer().beginFrame();
        scene->renderer().render();
        scene->renderer().endFrame();

        ecs::imgui::endFrame();
        window->swapBuffers();
        ecs::Time::endFrame();
    }
}

}