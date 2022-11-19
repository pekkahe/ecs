#pragma once

#include <core/Core.hpp>
#include <graphics/Shader.hpp>
#include <graphics/Texture.hpp>
#include <scene/Scene.hpp>
#include <ui/Window.hpp>

namespace eng
{
    class Window;
    class Camera;

    namespace gfx
    {
        class Renderer
        {
        public:
            Renderer();
            ~Renderer();

            void beginFrame();
            void render(const Scene& scene);
            void endFrame();

            void drawTriangle();
            void drawTwoTriangles();
            void drawTwoTrianglesWithOwnBuffers();
            void drawTwoTrianglesWithOwnBuffersAndPrograms();
            void drawRectangle();
            void drawTexture();
            void drawCube(const Camera& camera);

        private:
            std::vector<Shader> m_shaders;
            std::vector<Texture> m_textures;
        };
    }
}
