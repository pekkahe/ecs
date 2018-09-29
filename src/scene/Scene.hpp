#pragma once

#include <component/Database.hpp>
#include <component/Query.hpp>

#include <graphics/RenderSystem.hpp>

#include <scene/Camera.hpp>
#include <scene/TransformSystem.hpp>

namespace eng
{
	class Scene : public trait::non_copyable
	{
	public:
		Scene();
		~Scene();
		Scene(Scene&&) = default;
		Scene& operator=(Scene&&) = default;

		void createTestMesh();

		void update();

		EntityId createEntity();

		RenderSystem& renderer() { return m_renderSystem; }

		Camera& camera() { return m_camera; }
		const Camera& camera() const { return m_camera; }

		Query<> query() const;

	private:
		void registerSystem(System& system);

	private:
		Database m_database;
		
		std::vector<System*> m_systems;

		TransformSystem m_transformSystem;
		RenderSystem m_renderSystem;
		Camera m_camera;
	};
}
