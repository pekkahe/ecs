#pragma once

#include <component/System.hpp>

#include <graphics/Mesh.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Texture.hpp>

namespace eng
{
	class Scene;
	class RenderSystem : public System
	{
	public:
		RenderSystem(Database& db);
		virtual ~RenderSystem() override;

		virtual void update() override;

		void beginFrame();
		void render(const Scene& scene);
		void endFrame();

		// - owns components and operates on them
		// - doesn't care about entities, but components (?)
		// - e.g. do this for all Mesh components
		// - sync points for adding/removing components?

	private:
		TableRef<Mesh> m_meshes;

		std::vector<gfx::Shader> m_shaders;
		std::vector<gfx::Texture> m_textures;
	};
}

