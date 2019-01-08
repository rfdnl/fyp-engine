#ifndef TEST_RECT_HPP
#define TEST_RECT_HPP
#include "TestBase.hpp"


class TestRect : public TestBase
{
	glm::vec4 rgba = glm::vec4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(1.0f, 1.0f);
	float rotate = 0.0f;

public:
	TestRect(Engine& engine):TestBase(engine) {
		//
	}

	void Draw() override {
		engine.Graphics_DrawRect(translation, size, rotate, rgba);
	}

	void ImGuiDraw() override {
		ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 500.0f);
		ImGui::SliderFloat("Width", &size.x, 0.0f, 960.0f);
		ImGui::SliderFloat("Height", &size.y, 0.0f, 540.0f);
		ImGui::SliderFloat("Rotation", &rotate, 0.0f, 6.28318f);
		ImGui::ColorEdit4("Color", &rgba.x);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
};

#endif // TEST_SHADER_HPP
