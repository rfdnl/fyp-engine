#ifndef TEST_CLEAR_COLOR_HPP
#define TEST_CLEAR_COLOR_HPP

#include "TestBase.hpp"

class TestClearColor : public TestBase {
private:
	float color[4];
public:
	TestClearColor();
	~TestClearColor();

	void OnUpdate(std::chrono::duration<double> deltaTime) override;
	void OnRender() override;
	void OnImGuiRender() override;
};

#endif // TEST_CLEAR_COLOR_HPP
