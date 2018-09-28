#pragma once

namespace eng
{
	class Time
	{
	public:
		Time();

		void update(float frameTime);

		static float deltaTime() { return m_deltaTime; }

	private:
		// Time between current frame and last frame.
		static float m_deltaTime;
		// Time of last frame.
		float m_lastFrameTime = 0.0f;
	};
}
