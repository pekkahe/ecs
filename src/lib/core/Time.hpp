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
        Timer();
        ~Timer();
        Timer(Timer&&) = default;
        Timer& operator=(Timer&&) = default;

        void begin();

        double reset();
        double elapsed() const;

        static Timer start();

    private:
        std::chrono::steady_clock::time_point m_begin;
    };
}
