#include "Renderer.hpp"

Renderer::Renderer() :
	proj(glm::ortho(0.0f, static_cast<float>(Global::ScreenWidth()), 0.0f, static_cast<float>(Global::ScreenHeight()), -1.0f, 1.0f)),
	view(glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)))
{}

void Renderer::Init(){
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

	va.Init();
	vb.Init(position, 4 * 4 * sizeof(float));
	layout.Push<float>(2); // position
	layout.Push<float>(2); // texture coordinate
	va.AddBuffer(vb, layout);
	ib.Init(indices, 3 * 2);

	shader.Init("shader/Basic.shader");
	texture.Init("images/rect.png");

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
}

void Renderer::DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	Draw(texture, translation, size, rotate, rgba);
}

void Renderer::Close(){
	texture.Close();
	shader.Close();
	ib.Close();
	vb.Close();
	va.Close();
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
	shader.Bind();
	shader.SetUniform1i("u_Texture", 0);
	shader.SetUniform4f("myColor", rgba.x, rgba.y, rgba.z, rgba.w);
	shader.SetUniformMat4f("u_ModelViewProj", mvp);

	va.Bind();
	ib.Bind();
	glCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
