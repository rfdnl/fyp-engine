#ifndef TEST_INPUT_HPP
#define TEST_INPUT_HPP

#include "TestBase.hpp"

class TestInput : public TestBase {
public:
	TestInput(Engine& engine) : TestBase(engine){
		engine.Input_DEBUG(true);
	}

	~TestInput(){
		engine.Input_DEBUG(false);
	}
};

#endif // TEST_INPUT_HPP
