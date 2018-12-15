#pragma once

namespace eng
{
    class Engine
    {
    public:
        Engine();
        ~Engine();

        // Begin game loop.
        void execute();
        // Signal termination.
        void terminate();

    private:
        bool m_terminate = false;
    };
}
