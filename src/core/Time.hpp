#pragma once

namespace eng
{
	class Time
	{
	public:
		static void update(double frameTime);

		static float deltaTime() { return m_deltaTime; }

	private:
		Time();

	private:
		// Time between current frame and last frame.
		static float m_deltaTime;
		// Time at last frame.
		static double m_lastFrameTime;
	};
}
