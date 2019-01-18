#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "Graphics.hpp"

class Global {
	friend class Graphics;
	static unsigned int screenWidth;
    static unsigned int screenHeight;
	static void WindowResize(GLFWwindow* window, int width, int height);
public:
	static unsigned int ScreenWidth() { return screenWidth; }
	static unsigned int ScreenHeight() { return screenHeight; }
};

#endif // GLOBAL_HPP
