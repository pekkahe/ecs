#include <core/Core.hpp>
#include <scene/Scene.hpp>
#include <ui/Window.hpp>

#include <filesystem>

int main(int /*argc*/, char** /*argv*/)
{
    std::cout << "Running in " << std::filesystem::current_path() << std::endl;

    auto window = std::make_shared<ecs::Window>(640, 480, "Client");
    
    auto scene = std::make_shared<ecs::Scene>();
    scene->cameraSystem().registerWindow(*window);

    scene->createCube(ecs::vec3(-1.5f, 0.0f, -3.0f));
    scene->createCube(ecs::vec3(0.0f, 0.0f, -3.0f));
    scene->createCube(ecs::vec3(1.5f, 0.0f, -3.0f));
    
    while (window->pollEvents())
    {
        window->beginFrame();

        scene->update(window->frameInput());
        scene->render();

        window->endFrame();
    }
    
    return 0;
}
