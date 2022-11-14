#pragma once

namespace eng
{
    class Window;
    class Scene;

    class Engine
    {
    public:
        Engine();
        ~Engine();

        void execute(std::shared_ptr<Window> window, std::shared_ptr<Scene> scene);
    };
}
