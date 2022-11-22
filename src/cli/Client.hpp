#pragma once

namespace ecs
{
    class Window;
    class Scene;
}

namespace client
{
    void init();
    void deinit();

    void run(std::shared_ptr<ecs::Window> window, std::shared_ptr<ecs::Scene> scene);
}
