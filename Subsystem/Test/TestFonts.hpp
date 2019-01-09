#ifndef TEST_FONTS_HPP
#define TEST_FONTS_HPP

#include "TestBase.hpp"

class TestFonts : public TestBase {
public:
	TestFonts(Engine& engine):TestBase(engine){
		//engine.Fonts_Add("Arial20", "fonts/arial.ttf", 20);
	}

	~TestFonts(){
        //engine.Fonts_Clear();
	}

	void Draw() override {
		engine.Fonts_Write("Test Fonts", 0.0f, 0.0f, 1.0f, glm::vec3(1.0));
	}
};

#endif // TEST_FONTS_HPP
