#include "Renderer.hpp"

Renderer::Renderer()
{
	// test start
	float position[] = {
		0.0f, 0.0f, 	0.0f, 0.0f,		// bottom left 0
		1.0f, 0.0f, 	1.0f, 0.0f,		// bottom right 1
		1.0f, 1.0f, 	1.0f, 1.0f, 	// top right 2
		0.0f, 1.0f, 	0.0f, 1.0f		// top left 3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	va = std::make_shared<VertexArray>();
	vb = std::make_shared<VertexBuffer>(position, 4 * 4 * sizeof(float));
	layout->Push<float>(2); // position
	layout->Push<float>(2); // texture coordinate
	va->AddBuffer(*vb, *layout);
	ib = std::make_shared<IndexBuffer>(indices, 3 * 2);

	shader = std::make_shared<Shader>("shader/Basic.shader");
	rectangle = std::make_shared<Texture>("images/rect.png");

	va->Unbind();
	vb->Unbind();
	ib->Unbind();
}

void Renderer::DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	Draw(*rectangle, translation, size, rotate, rgba);
}

void Renderer::Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	glm::mat4 model;
	model = glm::translate(glm::mat4(1.0f), translation);
	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
	model = glm::scale(model, glm::vec3(size, 1.0f));
	glm::mat4 mvp = proj * view * model;

	texture.Bind();
	shader->Bind();
	//shader->SetUniformBool("UseTexture", true);
	shader->SetUniform1i("u_Texture", 0);
	shader->SetUniform4f("myColor", rgba.x, rgba.y, rgba.z, rgba.w);
	shader->SetUniformMat4f("u_ModelViewProj", mvp);

	va->Bind();
	ib->Bind();
	glCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));
}
