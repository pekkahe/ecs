#pragma once

#include <chrono>

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

    class Timer 
    {
    public:
        static Timer start();

        void begin();

        // Reset timer and return elapsed time in milliseconds.
        double reset();
        // Return elapsed time in milliseconds.
        double elapsed() const;

    private:
        std::chrono::steady_clock::time_point m_begin;
    };
}
