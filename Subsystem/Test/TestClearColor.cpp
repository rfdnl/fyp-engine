#include "TestClearColor.hpp"
#include "../Helper/IncludeGL.hpp"
#include "../Vendor/imgui/imgui.h"

TestClearColor::TestClearColor()
:color{ 0.2f, 0.3f, 0.8f, 1.0f }
{

}

TestClearColor::~TestClearColor(){

}


void TestClearColor::OnUpdate(std::chrono::duration<double> deltaTime){

}

void TestClearColor::OnRender(){
	glCall(glClearColor(color[0],color[1],color[2],color[3]));
	glCall(glClear(GL_COLOR_BUFFER_BIT));
}

void TestClearColor::OnImGuiRender(){
	ImGui::ColorEdit4("Clear Color", color);
}
