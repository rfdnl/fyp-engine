#ifndef TEST_FONTS_HPP
#define TEST_FONTS_HPP

#include "TestBase.hpp"

class TestFonts : public TestBase {
public:
	TestFonts(Engine& engine);
	~TestFonts();
	void Draw() override;
};

#endif // TEST_FONTS_HPP
