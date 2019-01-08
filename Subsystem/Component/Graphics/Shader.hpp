#ifndef SHADER_HPP
#define SHADER_HPP

#include <iostream>
#include <unordered_map>
#include "../../Helper/IncludeGL.hpp"
#include <glm/glm.hpp>

struct ShaderProgramSource{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::unordered_map<std::string, int> uniformLocationCache;
	std::string filepath;
	unsigned int buffer;
	int GetUniformLocation(const std::string& name);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	ShaderProgramSource ParseShader(const std::string& filepath);
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;
	unsigned int GetBuffer() const { return buffer; }

	// set uniforms
	void SetUniformBool(const std::string& name, bool on);
	void SetUniform1i(const std::string& name, int v);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
};

/*
	USAGE:

	// before draw
	Shader shader("shader/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("Color", 0.8f, 0.3f, 0.8f, 1.0f);

	shader.Unbind();

	// during draw
	shader.Bind();
	shader.SetUniform4f("Color", 0.8f, 0.3f, 0.8f, 1.0f);


*/

#endif // SHADER_HPP
