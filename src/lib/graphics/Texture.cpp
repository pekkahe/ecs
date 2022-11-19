#include <Precompiled.hpp>
#include <graphics/Texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace eng;
using namespace eng::gfx;

Texture::Texture(const std::string& path, GLint wrap, GLint filter, GLenum format)
{
    glGenTextures(1, &m_id.uint());
    glBindTexture(GL_TEXTURE_2D, m_id);

    // Set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);

    stbi_set_flip_vertically_on_load(true);

    // Load and generate the texture
    int width;
    int height;
    int numberOfChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &numberOfChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "ERROR::TEXTURE::Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture()
{
    if (m_id.valid())
    {
        glDeleteTextures(1, &m_id.uint());
    }
}
