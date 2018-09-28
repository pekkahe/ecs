#pragma once

#include <core/Defines.hpp>
#include <graphics/Id.hpp>

namespace eng
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

			// Set a uniform boolean value.
			void setBool(const std::string& name, bool value) const;
			// Set a uniform integer value.
			void setInt(const std::string& name, int value) const;
			// Set a uniform float value.
			void setFloat(const std::string& name, float value) const;
			// Set a uniform 4x4 matrix value.
			void setMatrix(const std::string& name, glm::mat4 value) const;

		private:
			std::string readFile(const std::string& path);

			void compileShader(unsigned int shader, const char* source);
			void checkCompilationErrors(unsigned int value, const char* type);

		private:
			// The OpenGL shader program ID.
			Id m_id = Id::Invalid;
		};
	}
}