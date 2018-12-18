#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <chrono>

class TestBase{
public:
	TestBase() {}
	virtual ~TestBase() {}

	virtual void OnUpdate(std::chrono::duration<double> deltaTime) {}
	virtual void OnRender() {}
	virtual void OnImGuiRender() {}
};

#endif // TEST_BASE_HPP
