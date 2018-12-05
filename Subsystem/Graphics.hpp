#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <vector>
#include <memory>
#include "Helper/IncludeGL.hpp"
#include "Helper/ILoggable.hpp"
#include "Component/Graphics/IDrawable.hpp"
#include "Component/Graphics/Texture.hpp"
#include "Component/Graphics/Shader.hpp"
#include "Component/Graphics/VertexArray.hpp"
#include "Component/Graphics/VertexBuffer.hpp"
#include "Component/Graphics/IndexBuffer.hpp"
#include "Component/Graphics/VertexBufferLayout.hpp"

class Graphics : public ILoggable{
	// test
	std::shared_ptr<VertexArray> va; //
	std::shared_ptr<VertexBuffer> vb; //
	std::shared_ptr<IndexBuffer> ib; //
	std::shared_ptr<VertexBufferLayout> layout;
	std::shared_ptr<Shader> shader; //
	float red = 0.0f;
	float increment = 0.05f;
	// test end

	std::vector<std::shared_ptr<Texture>> onFrame;
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

    Graphics(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Grfx"),
        layout(std::make_shared<VertexBufferLayout>())
    {
		std::cout << "Graphics()" << std::endl;
    }

    ~Graphics();

    bool Initialize();
    bool Create(const char* title, int width = DEFAULT_WIDTH, int height = DEFAULT_HEIGHT, int x = DEFAULT_POS, int y = DEFAULT_POS);
    bool IsOpen();
    void PollEvents();
    void Draw();
    std::shared_ptr<Texture> NewTexture(const char* filename);
	void Draw(std::shared_ptr<Texture> drawable);
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
    void Close();
};

#endif // GRAPHICS_HPP
