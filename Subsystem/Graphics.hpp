#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#ifndef GLFW_INCLUDE_GLU
#define GLFW_INCLUDE_GLU
#endif // GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>
#include <vector>
#include "Helper/ILoggable.hpp"
#include "Utility/IDrawable.hpp"
#include "Utility/Texture.hpp"

class Graphics : public ILoggable{
	std::vector<std::shared_ptr<Texture>> onFrame;
    GLFWwindow* window;
    static bool isOpen;
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool InitWindow();
    bool InitGraphics(int width, int height, int x, int y);
    static void WindowClosing(GLFWwindow* window);
    bool CheckError(std::string functionName, int line = -1, std::string comment = "NONE");
public:
    static const unsigned int DEFAULT_WIDTH = 640;
    static const unsigned int DEFAULT_HEIGHT = 480;
    static const int DEFAULT_POS = 100;

    Graphics(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Grfx")
    {}

    bool Initialize();
    bool Create(const char* title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int x = DEFAULT_POS, int y = DEFAULT_POS);
    bool IsOpen();
    void PollEvents();
    void Draw();
    std::shared_ptr<Texture> NewTexture(const char* filename);
	void Draw(std::shared_ptr<Texture> drawable);
    void Close();
};

#endif // GRAPHICS_HPP
