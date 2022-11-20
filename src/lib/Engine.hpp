#pragma once

namespace eng
{
    class Window;
    class Scene;
}

namespace engine
{
    void init();
    void deinit();

    void run(std::shared_ptr<eng::Window> window, std::shared_ptr<eng::Scene> scene);
}
