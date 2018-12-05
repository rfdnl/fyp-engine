#include "Shader.hpp"
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& filepath):filepath(filepath), buffer(0)
{
	std::cout << "Shader()" << std::endl;
	ShaderProgramSource source = ParseShader(filepath);
	buffer = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader(){
	std::cout << "~Shader()" << std::endl;
	glCall(glDeleteProgram(buffer));
}


void Shader::Bind() const{
	glCall(glUseProgram(buffer));
}

void Shader::Unbind() const{
	glCall(glUseProgram(0));
}

int Shader::GetUniformLocation(const std::string& name){
	glCall(int location = glGetUniformLocation(buffer, name.c_str()));
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
		return uniformLocationCache[name];

	if (location < -1){
		std::cout << "warning: uniform " << name << " does not exist!" << std::endl;
	}
	uniformLocationCache[name] = location;
	return location;
}

// set uniforms
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3){
	glCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath){
	std::ifstream stream(filepath);

	enum class ShaderType{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)){
		if (line.find("#shader") != std::string::npos){
			if (line.find("vertex") != std::string::npos){
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos){
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[(int)type] << line << '\n';
		}
	}
	return { ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source){
	glCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	glCall(glShaderSource(id, 1, &src, nullptr));
	glCall(glCompileShader(id));

	int result;
	glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
	if (result == GL_FALSE){
		int length;
		glCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)malloc(length* sizeof(char));
		glCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER? "vertex" : "fragment") << ", msg: " << message << std::endl;
		glCall(glDeleteShader(id));
		return 0;
	}
	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
	glCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glCall((glAttachShader(program, vs)));
	glCall((glAttachShader(program, fs)));
	glCall(glLinkProgram(program));
	glCall(glValidateProgram(program));

	glCall(glDeleteShader(vs));
	glCall(glDeleteShader(fs));

	return program;
}
