#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>
#include <memory>
#include "Helper/IncludeGL.hpp"
#include "Helper/ILoggable.hpp"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"
#include "Input.hpp"
#include "Global.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Renderer;
class Graphics : public ILoggable{
    GLFWwindow* window;
    static bool isOpen;
    static void WindowClosing(GLFWwindow* window);
    bool InitWindow();
    bool InitGraphics(int width, int height, int x, int y);
    bool CheckError(std::string functionName, int line = __LINE__);
public:
    Graphics(std::shared_ptr<Logger> logPtr);
    ~Graphics();

	// LIFE-CYCLE
    bool Initialize();
    bool Create(const char* title, int width, int height, int x = 100, int y = 100);
    bool IsOpen();
    void PollEvents();
    void SetClearColor(float red, float green, float blue, float alpha);
    void ClearColor();
    void ImGui_NewFrame();
    void ImGui_Draw();
    void Flush();
    void Close();

	// STATIC
	void SetWindowSize(int width, int height);
};

#endif // GRAPHICS_HPP
