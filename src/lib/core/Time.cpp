#include <Precompiled.hpp>
#include <core/Time.hpp>

#include <GLFW/glfw3.h>

using namespace eng;

constexpr std::chrono::milliseconds fixedFrameTime = std::chrono::milliseconds(16);

double Time::m_frameTime = 0.0f;
float Time::m_deltaTime = 0.0f;

// todo: measure framerate
// todo: fixed framerate 30/60 fps?

void Time::endFrame()
{
    double frameTime = glfwGetTime();
    //auto tim = std::chrono::high_resolution_clock::now();
    //auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(tim);

    m_deltaTime = static_cast<float>(frameTime - m_frameTime);
    m_frameTime = frameTime;

    //SHOE_LOG("Delta time: %f", m_deltaTime);

    //float deltaTimeMs = m_deltaTime * 1000.0f;
    //auto duration = std::chrono::duration<float, std::milli>(deltaTimeMs);
    //auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    //auto untilFrame = fixedFrameTime - durationMs;
    //if (untilFrame.count() > 0)
    //{
    //    std::this_thread::sleep_for(untilFrame);
    //}
}

float Time::deltaTime()
{
    return m_deltaTime;
}

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::begin()
{
    m_begin = std::chrono::steady_clock::now();
}

double Timer::elapsed() const
{
    using namespace std::chrono;

    return duration_cast<microseconds>(
        steady_clock::now() - m_begin).count() / 1'000'000.0;
}

double Timer::reset()
{
    using namespace std::chrono;

    double e = elapsed();
    begin();
    return e;
}

Timer Timer::start()
{
    Timer timer;
    timer.begin();
    return timer;
}