#ifndef INPUT_HPP
#define INPUT_HPP

#include "Graphics.hpp"
#include "Component/Input/Keyboard.hpp"

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

	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
		currentKey = key;
		currentAction = action;
		currentScan = scancode;
		currentModifier = mods;

		if (DEBUG && (KeyPress(key) || KeyRelease(key) || KeyRepeat(key))){
			std::cout <<
			(KeyPress(key)? "KeyPress:" :
				(KeyRelease(key)? "KeyRelease:" :
					"KeyRepeat:")
			)
			<< Name(key) << std::endl;
		}
	}

	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
		mouseButton = button;
		mouseAction = action;
		mouseModifier = mods;

		if (DEBUG && (MousePress(button) || MouseRelease(button))){
			std::cout << (MousePress(button)? "MousePress:" : "MouseRelease:")
				<< ", x:" << mouseXpos
				<< ", y:" << mouseYpos
			<< std::endl;
		}
	}

	static void MousePositionCallback(GLFWwindow* window, double xpos, double ypos){
		mouseXpos = xpos;
		mouseYpos = ypos;
	}

public:
	static bool DEBUG; // true to print mouse and keyboard states

	static bool KeyPress(int key){
		return currentKey == key && currentAction == GLFW_PRESS;
	}

	static bool KeyRelease(int key){
		return currentKey == key && currentAction == GLFW_RELEASE;
	}

	static bool KeyRepeat(int key){
		return currentKey == key && currentAction == GLFW_REPEAT;
	}

	static bool MousePress(int button){
		return mouseButton == button && mouseAction == GLFW_PRESS;
	}

	static bool MouseRelease(int button){
		return mouseButton == button && mouseAction == GLFW_RELEASE;
	}

	static void MousePos(double& xpos, double& ypos){
		xpos = mouseXpos;
		ypos = mouseYpos;
	}

	static const char* Name(int key){
		const char* keyName = glfwGetKeyName(key, currentScan);
		return keyName != NULL? keyName : "(non-printable)";
	}
};

#endif // INPUT_HPP
