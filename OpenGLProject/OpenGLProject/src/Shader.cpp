#include "Shader.h"
#include "GL/glew.h"


#include <sstream>
#include <iostream>
#include <fstream>


Shader::Shader(const std::string& filepath) : m_RendererID(0), m_FilePath(filepath)
{
    // compiles a shader to be used by opengl. Shaders are programs that run on GPU instead of CPU
    ShaderProgramSource source = ParseShader(filepath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
    
}

Shader::~Shader()
{
    glDeleteProgram(m_RendererID);
    glUseProgram(0);
}

ShaderProgramSource Shader::ParseShader(const std::string& file) {
    std::ifstream stream(file);
    std::string line;

    enum ShaderType {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };
    ShaderType type = ShaderType::NONE;

    std::stringstream shaderStream[2];

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            shaderStream[(int)type] << line << '\n';
        }
    }

    return { shaderStream[0].str(), shaderStream[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result); 

    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length); 
        char* message = new char[length];
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex shader" : "fragment shader") << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        delete[] message;
        return 0;
    }

    return id;
}

int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    return program;
}

void Shader::Bind() const
{
    glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    int location = getUniformLocation(name);
    glUniform4f(location, v0, v1, v2, v3);
}

void Shader::SetUniform1i(const std::string& name, int v0)
{
    int location = getUniformLocation(name);
    glUniform1i(location, v0);
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    int location = getUniformLocation(name);
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void Shader::SetUniform1iv(const std::string& name, int count, int* vec)
{
    int location = getUniformLocation(name);
    glUniform1iv(location, count, vec);
}

int Shader::getUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
        return m_UniformLocationCache[name];
    }
    
    
    int location = glGetUniformLocation(m_RendererID, name.c_str());
    if (location == -1) { //uniform doesn't exist.
        std::cout << "Uniform " << name << "doesn't exist in the shader.";
    }
    else {
        m_UniformLocationCache[name] = location;
    }
	return location;
}
