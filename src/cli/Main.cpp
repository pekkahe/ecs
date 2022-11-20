#include <Precompiled.hpp>
#include <Engine.hpp>

#include <core/Core.hpp>
#include <ui/Window.hpp>
#include <scene/Scene.hpp>
#include <filesystem>

int main(int /*argc*/, char** /*argv*/)
{
    using namespace eng;
    
    std::cout << "Running in " << std::filesystem::current_path() << std::endl;
    engine::init();
    // FIX: Failed to init opengl loader
    auto window = std::make_shared<Window>(640, 480, "Engine");

    // TODO: Remove ctor dependency Scene->Window
    auto scene = std::make_shared<Scene>(window);
    scene->createCube(vec3(-1.5f, 0.0f, -3.0f));
    scene->createCube(vec3(0.0f, 0.0f, -3.0f));
    scene->createCube(vec3(1.5f, 0.0f, -3.0f));

    engine::run(window, scene);
    engine::deinit();

    return 0;
}
