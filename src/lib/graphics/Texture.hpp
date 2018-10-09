#pragma once

#include <core/Defines.hpp>
#include <graphics/Id.hpp>

#include <glad/glad.h>

namespace eng
{
    namespace gfx
    {
        class Texture
        {
        public:
            Texture(const std::string& path, GLint wrap, GLint filter, GLenum format);
            ~Texture();
            // Move only.
            Texture(const Texture&) = delete;
            Texture& operator=(const Texture&) = delete;
            Texture(Texture&& other) = default;
            Texture& operator=(Texture&& other) = default;

            const Id& id() const { return m_id; }

        private:
            // The OpenGL texture ID.
            Id m_id = Id::Invalid;
        };
    }
}