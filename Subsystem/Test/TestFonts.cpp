#include "TestFonts.hpp"

TestFonts::TestFonts(Engine& engine):TestBase(engine){
}

TestFonts::~TestFonts(){
}

void TestFonts::Draw() {
	engine.Fonts_Write("Test Fonts", 0.0f, 0.0f, 1.0f, glm::vec3(1.0));
}
