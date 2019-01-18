#include "TestInput.hpp"

TestInput::TestInput(Engine& engine) : TestBase(engine){
	engine.Input_DEBUG(true);
}

TestInput::~TestInput(){
	engine.Input_DEBUG(false);
}
