#include "TestRect.hpp"

TestRect::TestRect(Engine& engine):TestBase(engine) {
}

void TestRect::Draw() {
	engine.Render_DrawRect(translation, size, rotate, rgba);
}

void TestRect::ImGuiDraw() {
	ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 500.0f);
	ImGui::SliderFloat("Width", &size.x, 0.0f, Global::ScreenWidth());
	ImGui::SliderFloat("Height", &size.y, 0.0f, Global::ScreenHeight());
	ImGui::SliderFloat("Rotation", &rotate, 0.0f, 6.28318f);
	ImGui::ColorEdit4("Color", &rgba.x);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
}
