#pragma once

#include <core/Core.hpp>
#include <render/Id.hpp>

namespace ecs
{
    namespace gfx
    {
        class Shader
        {
        public:
            // Read and build a new shader.
            Shader(const std::string& vertexPath, const std::string& fragmentPath);
            ~Shader();
            // Move only.
            Shader(const Shader&) = delete;
            Shader& operator=(const Shader&) = delete;
            Shader(Shader&& other) = default;
            Shader& operator=(Shader&& other) = default;

            // Use/activate the shader.
            void use();

            void setBool(const std::string& name, bool value) const;
            void setInt(const std::string& name, int value) const;
            void setFloat(const std::string& name, float value) const;
            void setVec3(const std::string& name, vec3 value) const;
            void setMat4(const std::string& name, mat4 value) const;

        private:
            // The OpenGL shader program ID.
            Id m_id = Id::Invalid;
        };
    }
}