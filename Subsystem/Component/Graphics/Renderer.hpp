#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../../Global.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer{
private:
	glm::mat4 proj;
	glm::mat4 view;
	VertexBufferLayout layout;
	VertexArray va;
	VertexBuffer vb;
	IndexBuffer ib;
	Shader shader;
	Texture texture;
public:
	Renderer();
	~Renderer(){}
	void Init();
	void Close();
	void Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba);
	void DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba);
};

#endif // RENDERER_HPP
