#include <Precompiled.hpp>
#include <Engine.hpp>

#include <scene/Scene.hpp>
#include <ui/ImGui.hpp>

namespace engine
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

    eng::imgui::init();
}

void deinit()
{
    eng::imgui::deinit();

    glfwTerminate();
}

void run(std::shared_ptr<eng::Window> window, std::shared_ptr<eng::Scene> scene)
{
    while (window->pollEvents())
    {
        eng::imgui::beginFrame();

        scene->update();
        
        scene->renderer().beginFrame();
        scene->renderer().render();
        scene->renderer().endFrame();

        eng::imgui::endFrame();
        window->swapBuffers();
        eng::Time::endFrame();
    }
}

} // namespace ecs