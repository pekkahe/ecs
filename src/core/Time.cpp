#include <Precompiled.hpp>
#include <core/Time.hpp>

using namespace eng;

float Time::m_deltaTime = 0.0f;
double Time::m_lastFrameTime = 0.0f;

Time::Time()
{
}

void Time::update(double frameTime)
{
	m_deltaTime = static_cast<float>(frameTime - m_lastFrameTime);
	m_lastFrameTime = frameTime;
}
