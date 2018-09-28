#pragma once

#include <core/Defines.hpp>

namespace eng
{
	class Scene;
	class SceneSystem : public trait::non_copyable_nor_movable
	{
	public:
		SceneSystem();
		~SceneSystem();

		std::shared_ptr<Scene> createScene();

	private:
		std::vector<std::shared_ptr<Scene>> m_scenes;
	};
}