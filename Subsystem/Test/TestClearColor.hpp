#ifndef TEST_CLEAR_COLOR_HPP
#define TEST_CLEAR_COLOR_HPP

#include "TestBase.hpp"

class TestClearColor : public TestBase {
private:
	float color[4];
public:
	TestClearColor(Engine& engine);
	~TestClearColor();
	void Draw() override;
	void ImGuiDraw() override;
};

#endif // TEST_CLEAR_COLOR_HPP
