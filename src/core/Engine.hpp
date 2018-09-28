#pragma once

#include <graphics/RenderSystem.hpp>
#include <scene/SceneSystem.hpp>
#include <view/WindowSystem.hpp>

namespace eng
{
	class Engine
	{
	public:
		Engine();
		~Engine();

		// Begin game loop. Must be called from main thread.
		void execute();
		// Signal termination.
		void terminate();

	private:
		WindowSystem m_windowSystem;
		SceneSystem m_sceneSystem;
		//RenderSystem m_renderSystem;

		bool m_running = false;
	};
}
