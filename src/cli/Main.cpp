#include <Precompiled.hpp>
#include <core/Core.hpp>
#include <core/Engine.hpp>
#include <ui/Window.hpp>
#include <scene/Scene.hpp>

int main()
{
    using namespace eng;
    
    std::cout << "Starting engine." << std::endl;
    
    auto window = std::make_shared<Window>(640, 480, "Engine");

    // TODO: Remove ctor dependency Scene->Window
    auto scene = std::make_shared<Scene>(window);
    scene->createCube(vec3(-1.5f, 0.0f, -3.0f));
    scene->createCube(vec3(0.0f, 0.0f, -3.0f));
    scene->createCube(vec3(1.5f, 0.0f, -3.0f));

    eng::Engine engine;
    engine.execute(window, scene);
    
    std::cout << "Terminating engine." << std::endl;
    return 0;
}
