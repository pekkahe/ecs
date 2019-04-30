#include <Precompiled.hpp>
#include <core/Time.hpp>

using namespace eng;

constexpr std::chrono::milliseconds fixedFrameTime = std::chrono::milliseconds(16);

double Time::m_frameTime = 0.0f;
float Time::m_deltaTime = 0.0f;

// todo: measure framerate
// todo: fixed framerate 30/60 fps?

void Time::endFrame()
{
    double frameTime = glfwGetTime();

    m_deltaTime = static_cast<float>(frameTime - m_frameTime);
    m_frameTime = frameTime;
}

float Time::deltaTime()
{
    return m_deltaTime;
}

void Timer::begin()
{
    m_begin = std::chrono::steady_clock::now();
}

double Timer::elapsed() const
{
    using namespace std::chrono;

    return duration_cast<microseconds>(
        steady_clock::now() - m_begin).count() / 1'000.0;
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