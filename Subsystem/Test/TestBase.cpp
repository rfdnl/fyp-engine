#include "TestBase.hpp"

TestMenu::TestMenu(Engine& engine, TestBase*& currentTestPtr)
: TestBase(engine), currentTest(currentTestPtr){
	//
}

void TestMenu::ImGuiDraw(){
	for(auto& test : tests){
		if (ImGui::Button(test.first.c_str())){
			currentTest = test.second();
			engine.Audio_Play("test", "tick");
		}
	}
}
