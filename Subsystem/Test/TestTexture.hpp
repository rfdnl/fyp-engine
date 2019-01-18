#ifndef TEST_TEXTURE_HPP
#define TEST_TEXTURE_HPP

#include "TestBase.hpp"
class Texture;

class TestTexture : public TestBase {
	glm::vec4 rgba = glm::vec4(1.0f);
	glm::vec3 translation = glm::vec3(0.0f);
	glm::vec2 size = glm::vec2(1.0f, 1.0f);
	float rotate = 0.0f;
	Texture texture;
public:
	TestTexture(Engine& engine);
	~TestTexture();
	void Draw() override;
	void ImGuiDraw() override;
};

#endif // TEST_TEXTURE_HPP
