#include "TestClearColor.hpp"

TestClearColor::TestClearColor(Engine& engine)
:TestBase(engine), color{ 0.2f, 0.3f, 0.8f, 1.0f }
{}

void TestClearColor::Draw(){
	engine.Graphics_SetBackgroundColor(color[0],color[1],color[2],color[3]);
	engine.Graphics_ClearColor();
}

void TestClearColor::ImGuiDraw(){
	ImGui::ColorEdit4("Clear Color", color);
}
