#ifndef TEST_TEXTURE_HPP
#define TEST_TEXTURE_HPP

#include "TestBase.hpp"
#include "../Component/Graphics/Texture.hpp"

class TestTexture : public TestBase {
	glm::vec4 rgba = glm::vec4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(1.0f, 1.0f);
	float rotate = 0.0f;
	Texture texture;
public:
	TestTexture(Engine& engine)
	: TestBase(engine), texture("images/test2.png")
	{
		size.x = texture.Width();
		size.y = texture.Height();
	}

	void Draw() override {
		engine.Graphics_Draw(texture, translation, size, rotate, rgba);
	}

	void ImGuiDraw() override {
		ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 500.0f);
		ImGui::SliderFloat("Width", &size.x, 0.0f, texture.Width());
		ImGui::SliderFloat("Height", &size.y, 0.0f, texture.Height());
		ImGui::SliderFloat("Rotation", &rotate, 0.0f, 6.28318f);
		ImGui::ColorEdit4("Color", &rgba.x);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
};

#endif // TEST_TEXTURE_HPP
