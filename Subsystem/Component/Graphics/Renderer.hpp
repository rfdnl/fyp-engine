#ifndef RENDERER_HPP
#define RENDERER_HPP

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
	std::shared_ptr<VertexArray> va; //
	std::shared_ptr<VertexBuffer> vb; //
	std::shared_ptr<IndexBuffer> ib; //
	std::shared_ptr<VertexBufferLayout> layout = std::make_shared<VertexBufferLayout>();
	std::shared_ptr<Shader> shader; //
	std::shared_ptr<Texture> rectangle;
	//glm::vec3 translation = glm::vec3(0, 0, 0);
	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
public:
	Renderer();
	~Renderer(){}
	void Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba);
	void DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba);
};

#endif // RENDERER_HPP
