#pragma once

namespace eng
{
    class Time
    {
    public:
        static void endFrame();

        // Last frame time in seconds.
        static float deltaTime();

    private:
        static double m_frameTime;
        static float m_deltaTime;
    };

}
