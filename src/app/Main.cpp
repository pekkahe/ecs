#include <core/Core.hpp>
#include <scene/Scene.hpp>
#include <ui/ImGui.hpp>
#include <ui/Window.hpp>

#include <filesystem>

namespace client
{
    
void onGlfwError(int error, const char* description)
{
    ECS_LOG_ERROR("%s [GLFW #%d]", description, error);
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

} // namespace client

int main(int /*argc*/, char** /*argv*/)
{
    using namespace ecs;
    
    std::cout << "Running in " << std::filesystem::current_path() << std::endl;
    client::init();

    auto window = std::make_shared<Window>(640, 480, "Client");

    // TODO: Remove ctor dependency Scene->Window
    auto scene = std::make_shared<Scene>(window);
    scene->createCube(vec3(-1.5f, 0.0f, -3.0f));
    scene->createCube(vec3(0.0f, 0.0f, -3.0f));
    scene->createCube(vec3(1.5f, 0.0f, -3.0f));

    client::run(window, scene);
    client::deinit();

    return 0;
}
