#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GLFW/glfw3.h> // window library

class Window{
private:
    GLFWwindow* window;
public:
    static const int DEFAULT_WIDTH = 640;
    static const int DEFAULT_HEIGHT = 480;
    static const int DEFAULT_POS = 50;
    bool Init();
    bool Create(const char* title, int width, int height, int x, int y);
    void End();
};

#endif // WINDOW_HPP
