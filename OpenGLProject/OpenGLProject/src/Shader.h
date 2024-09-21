#pragma once
#include "string"
#include "unordered_map"
#include "glm/glm.hpp"

struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();


	void Bind() const;
	void Unbind() const;

	//Uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniform1i(const std::string& name, int v0);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void SetUniform1iv(const std::string& name, int count, int* vec);
private:
	int getUniformLocation(const std::string& name);
	ShaderProgramSource ParseShader(const std::string& file);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
};

