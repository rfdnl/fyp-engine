#ifndef INPUT_HPP
#define INPUT_HPP

#include "Component/Input/Keyboard.hpp"
#include "Component/Input/Mouse.hpp"

class Input {
	friend class Graphics;

	static int currentKey;
	static int currentAction;
	static int currentModifier;
	static int currentScan;

	static int mouseButton;
	static int mouseAction;
	static int mouseModifier;

	static double mouseXpos;
	static double mouseYpos;

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos);
public:
	static bool DEBUG; // true to print mouse and keyboard states

	static bool KeyPress(int key);
	static bool KeyRelease(int key);
	static bool KeyRepeat(int key);
	static bool MousePress(int button);
	static bool MouseRelease(int button);
	static void MousePos(double& xpos, double& ypos);
	static const char* Name(int key);
};

#endif // INPUT_HPP
