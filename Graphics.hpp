#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#ifndef GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLU
#endif // GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>
#include "ILoggable.hpp"

class Graphics : public ILoggable{
    GLFWwindow* window;
    bool InitWindow();
    bool InitGraphics();
    static void WindowClosing(GLFWwindow* window);
public:
    static const int DEFAULT_WIDTH = 640;
    static const int DEFAULT_HEIGHT = 480;
    static const int DEFAULT_POS = 100;

    Graphics(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Graphics")
    {}

    bool Initialize();
    bool Create(const char* title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int x = DEFAULT_POS, int y = DEFAULT_POS);
    bool ShouldClose();
    void PollEvents();
    void Draw();
    void Close();
};

#endif // GRAPHICS_HPP
