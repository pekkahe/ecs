#include <Precompiled.hpp>
#include <scene/SceneSystem.hpp>
#include <scene/Scene.hpp>

using namespace eng;

SceneSystem::SceneSystem()
{
}

SceneSystem::~SceneSystem()
{
}

std::shared_ptr<Scene> SceneSystem::createScene()
{
	auto scene = std::make_shared<Scene>();

	m_scenes.emplace_back(scene);

	return scene;
}
