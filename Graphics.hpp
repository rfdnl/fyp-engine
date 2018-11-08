#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#ifndef GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLU
#endif // GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h> // window library
#include "Logger.hpp"
#include "ILoggable.hpp"
#include <sstream>

class Graphics : public ILoggable{
private:
    GLFWwindow* window;
    bool InitWindow();
    bool InitGraphics();
    static void WindowClosing(GLFWwindow* window);
public:
    static const int DEFAULT_WIDTH = 640;
    static const int DEFAULT_HEIGHT = 480;
    static const int DEFAULT_POS = 50;

    Graphics(Logger* logPtr);
    bool Init();
    bool Create(const char* title, int width, int height, int x, int y);
    bool ShouldClose();
    void PollEvents();
    void Draw();
    void Close();
};

#endif // GRAPHICS_HPP
