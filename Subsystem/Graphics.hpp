#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>
#include <memory>
#include "Helper/IncludeGL.hpp"
#include "Helper/ILoggable.hpp"
#include "Component/Graphics/Renderer.hpp"
#include "Vendor/imgui/imgui.h"
#include "Vendor/imgui/imgui_impl_glfw.h"
#include "Vendor/imgui/imgui_impl_opengl3.h"
#include "Input.hpp"

class Graphics : public ILoggable{
	// test
	std::shared_ptr<Renderer> renderer;
	// test end

    GLFWwindow* window;
    static bool isOpen;
    unsigned int screenWidth;
    unsigned int screenHeight;
    bool InitWindow();
    bool InitGraphics(int width, int height, int x, int y);
    static void WindowClosing(GLFWwindow* window);
    bool CheckError(std::string functionName, int line = __LINE__);
public:
    static const unsigned int DEFAULT_WIDTH = 640;
    static const unsigned int DEFAULT_HEIGHT = 480;
    static const int DEFAULT_POS = 100;

    Graphics(std::shared_ptr<Logger> logPtr);

    ~Graphics();

    bool Initialize();
    bool Create(const char* title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int x = DEFAULT_POS, int y = DEFAULT_POS);
    bool IsOpen();
    void PollEvents();
    void Close();
    void SetClearColor(float red, float green, float blue, float alpha);
    void ClearColor();
    void ImGui_NewFrame();
    void ImGui_Draw();
    void Flush();

    void Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
		renderer->Draw(texture, translation, size, rotate, rgba);
    }

    void DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
		renderer->DrawRect(translation, size, rotate, rgba);
    }
};

#endif // GRAPHICS_HPP
