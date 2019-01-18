#include "TestTexture.hpp"

TestTexture::TestTexture(Engine& engine)
: TestBase(engine)
{
	texture.Init("images/cat.png");
	size.x = texture.Width();
	size.y = texture.Height();
}

TestTexture::~TestTexture(){
	texture.Close();
}

void TestTexture::Draw() {
	engine.Render_Draw(texture, translation, size, rotate, rgba);
}

void TestTexture::ImGuiDraw() {
	ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 500.0f);
	ImGui::SliderFloat("Width", &size.x, 0.0f, texture.Width() * 10);
	ImGui::SliderFloat("Height", &size.y, 0.0f, texture.Height() * 10);
	ImGui::SliderFloat("Rotation", &rotate, 0.0f, 6.28318f);
	ImGui::ColorEdit4("Color", &rgba.x);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
