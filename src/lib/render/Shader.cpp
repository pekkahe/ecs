#include <Precompiled.hpp>
#include <render/Shader.hpp>

#include <glad/glad.h>

using namespace eng;
using namespace eng::gfx;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    // Read vertex shader source and compile
    std::string vertexCode = readFile(vertexPath);
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexShader, vertexCode.c_str());
    checkCompilationErrors(vertexShader, "VERTEX");
    
    // Read fragment shader source and compile
    std::string fragmentCode = readFile(fragmentPath);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentShader, fragmentCode.c_str());
    checkCompilationErrors(fragmentShader, "FRAGMENT");

    // Create shader program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader);
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    checkCompilationErrors(m_id, "PROGRAM");

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if (m_id.valid())
    {
        glDeleteProgram(m_id);
    }
}

std::string Shader::readFile(const std::string& path)
{
    std::ifstream fileStream;
    // Ensure ifstream object can throw exceptions
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    std::string source;
    try
    {
        // Open file
        fileStream.open(path.c_str());
        
        // Read file's buffer source into stream
        std::stringstream stringStream;
        stringStream << fileStream.rdbuf();

        // Close file handler
        fileStream.close();

        // Convert stream into string
        source = stringStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return source;
}

void Shader::compileShader(unsigned int shader, const char* source)
{
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);
}

void Shader::checkCompilationErrors(unsigned int value, const char* type)
{
    int  success;
    char infoLog[512];

    if (type == "PROGRAM")
    {
        glGetProgramiv(value, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(value, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::LINKING_FAILED\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetShaderiv(value, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(value, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::" << type << "::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
    }
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, vec3 value) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, value.x, value.y, value.z);
}

void Shader::setMat4(const std::string& name, mat4 value) const
{
    auto location = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}


