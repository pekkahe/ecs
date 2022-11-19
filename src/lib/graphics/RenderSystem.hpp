#pragma once

#include <core/ecs/System.hpp>
#include <graphics/Mesh.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Texture.hpp>

namespace eng
{
    class RenderSystem : public System
    {
    public:
        ADD_COMPONENT_FUNCTION(Mesh, m_meshTable);

    public:
        RenderSystem(Database& db);
        ~RenderSystem() override;

        void update(const Scene& scene) override;

        void beginFrame();
        void render();
        void endFrame();

    private:
        TableRef<Mesh> m_meshTable;

        std::vector<gfx::Shader> m_shaders;
        std::vector<gfx::Texture> m_textures;
    };
}

