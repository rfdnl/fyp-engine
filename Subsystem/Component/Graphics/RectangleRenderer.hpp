#ifndef RECTANGLE_RENDERER_HPP
#define RECTANGLE_RENDERER_HPP

#include <memory>
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class RectangleRenderer{
	std::shared_ptr<VertexArray> va; //
	std::shared_ptr<VertexBuffer> vb; //
	std::shared_ptr<IndexBuffer> ib; //
	std::shared_ptr<VertexBufferLayout> layout = std::make_shared<VertexBufferLayout>();
	std::shared_ptr<Shader> shader; //
	//glm::vec3 translation = glm::vec3(0, 0, 0);
	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
public:
	RectangleRenderer(){
		float position[] = {
			-0.5f, -0.5f,	// 0
			0.5f, -0.5f, 	// 1
			0.5f, 0.5f, 	// 2
			-0.5f, 0.5f		// 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		va = std::make_shared<VertexArray>();
		vb = std::make_shared<VertexBuffer>(position, 4 * 2 * sizeof(float));
		layout->Push<float>(2);
		va->AddBuffer(*vb, *layout);
		ib = std::make_shared<IndexBuffer>(indices, 3 * 2);
		shader = std::make_shared<Shader>("shader/Basic.shader");
		shader->Bind();
		shader->SetUniform4f("myColor", 0.5f, 0.3f, 0.8f, 1.0f);
		va->Unbind();
		vb->Unbind();
		ib->Unbind();
		shader->Unbind();
	}

	~RectangleRenderer(){}

	void Draw(glm::vec3 translation, glm::vec4 rgba){
		shader->Bind();
		va->Bind();
		ib->Bind();
		glCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
};

#endif // RECTANGLE_RENDERER_HPP
