#include <Precompiled.hpp>
#include <core/Time.hpp>

using namespace eng;

float Time::m_deltaTime = 0.0f;

Time::Time()
{
	m_deltaTime = 0.0f;
}

void Time::update(float frameTime)
{
	m_deltaTime = frameTime - m_lastFrameTime;
	m_lastFrameTime = frameTime;
}
