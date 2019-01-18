#include "Input.hpp"

bool Input::DEBUG = false;

int Input::currentKey = -1;
int Input::currentAction = -1;
int Input::currentModifier = -1;
int Input::currentScan = -1;

int Input::mouseButton = -1;
int Input::mouseModifier = -1;
int Input::mouseAction = -1;

double Input::mouseXpos = 0.0;
double Input::mouseYpos = 0.0;

bool Input::KeyPress(int key){
	return currentKey == key && currentAction == GLFW_PRESS;
}

bool Input::KeyRelease(int key){
	return currentKey == key && currentAction == GLFW_RELEASE;
}

bool Input::KeyRepeat(int key){
	return currentKey == key && currentAction == GLFW_REPEAT;
}

bool Input::MousePress(int button){
	return mouseButton == button && mouseAction == GLFW_PRESS;
}

bool Input::MouseRelease(int button){
	return mouseButton == button && mouseAction == GLFW_RELEASE;
}

void Input::MousePos(double& xpos, double& ypos){
	xpos = mouseXpos;
	ypos = mouseYpos;
}

const char* Input::Name(int key){
	const char* keyName = glfwGetKeyName(key, currentScan);
	return keyName != NULL? keyName : "(non-printable)";
}

void Input::KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
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

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods){
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

void Input::MousePositionCallback(GLFWwindow* window, double xpos, double ypos){
	mouseXpos = xpos;
	mouseYpos = ypos;
}
