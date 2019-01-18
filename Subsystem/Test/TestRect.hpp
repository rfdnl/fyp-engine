#ifndef TEST_RECT_HPP
#define TEST_RECT_HPP

#include "../Global.hpp"
#include "TestBase.hpp"

class TestRect : public TestBase
{
	glm::vec4 rgba = glm::vec4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(1.0f, 1.0f);
	float rotate = 0.0f;

public:
	TestRect(Engine& engine);
	void Draw() override;
	void ImGuiDraw() override;
};

#endif // TEST_SHADER_HPP
