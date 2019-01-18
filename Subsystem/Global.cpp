#include "Global.hpp"

unsigned int Global::screenWidth = 960.0f;
unsigned int Global::screenHeight = 540.0f;

void Global::WindowResize(GLFWwindow* window, int width, int height){
	screenWidth = width;
	screenHeight = height;
}
