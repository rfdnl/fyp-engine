#ifndef TEST_BASE_HPP
#define TEST_BASE_HPP

#include <iostream>
#include <chrono>
#include <vector>
#include <functional>
#include "../Engine.hpp"
#include "../Vendor/imgui/imgui.h"

class TestBase{
protected:
	Engine& engine;
public:
	TestBase(Engine& engine):engine(engine) {}
	virtual ~TestBase() {}
	virtual void Update(std::chrono::duration<double> deltaTime) {}
	virtual void Draw() {}
	virtual void ImGuiDraw() {}
};

class TestMenu : public TestBase {
private:
	TestBase*& currentTest;
	std::vector<std::pair<std::string, std::function<TestBase*()>>> tests;
public:
	TestMenu(Engine& engine, TestBase*& currentTestPtr);
	void ImGuiDraw() override;

	template<typename T>
	void RegisterTest(const std::string& name){
		std::cout << "Registering test: " << name << std::endl;
		tests.push_back(
			std::make_pair(
					name,
					[&, this](){ // & = reference capture
						return new T(engine);
					}
				)
			);
	}
};

#endif // TEST_BASE_HPP
