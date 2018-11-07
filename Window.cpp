#include "Window.hpp"
#include <iostream>
#include <stdlib.h>
#include <GLFW/glfw3.h> // window library

bool Window::Init(){
    if (glfwInit() != GL_TRUE){
        std::cout << "ERROR::GLFW: Could not initialize GLFW" << std::endl;
        return false;
    }
    std::cout << "GLFW: ready" << std::endl;
    return true;

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
}

bool Window::Create(const char* title, int width, int height, int x, int y){
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window){
        std::cout << "ERROR::GLFW: Could not create window" << std::endl;
        glfwTerminate();
        return false;
    }
    std::cout << "GLFW: created" << std::endl;
    glfwSetWindowPos(window, x, y);
    glfwMakeContextCurrent(window);
    glfwShowWindow(window);
    return true;
}

void Window::End(){
    glfwDestroyWindow(window);
    glfwTerminate();
}
