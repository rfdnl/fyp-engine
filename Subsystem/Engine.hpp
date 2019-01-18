#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <iostream>
#include <chrono>
#include "Helper/ILoggable.hpp"
#include "Component/Graphics/Texture.hpp"
#include "Component/Graphics/Renderer.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"

class Engine : public ILoggable
{
    bool running = true;
    Graphics graphics;
    Fonts fonts;
    Audio audio;
    Renderer renderer;
protected:
    Engine(std::shared_ptr<Logger> logPtr);
    bool IsRunning();
    bool IsOpen();
    bool Initialize();
    void Start();
    void InputProcessing();
    void Update(std::chrono::duration<double> deltaTime);
    void Draw();
    void Exit();
    void End();
public:
    // AUDIO
    void Audio_NewSource(std::string sourceKey);
    bool Audio_NewBuffer(std::string audioKey, const char* filePath);
    void Audio_Play(std::string sourceKey, std::string audioKey);
    bool Audio_CanPlay(std::string sourceKey);

    // GRAPHICS
    void Graphics_SetBackgroundColor(float red, float green, float blue, float alpha = 255.0f);
    void Graphics_ClearColor();
    void Graphics_ImGui_NewFrame();
    void Graphics_ImGui_Draw();
    void Graphics_Flush();

    void Render_Draw(const Texture& texture, glm::vec3 translation = glm::vec3(0.0f), glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec4 rgba = glm::vec4(1.0f));
	void Render_DrawRect(glm::vec3 translation = glm::vec3(0.0f), glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec4 rgba = glm::vec4(1.0f));

	// INPUT
	void Input_DEBUG(bool on);
	bool Input_KeyPress(int key);
	bool Input_KeyRelease(int key);
	bool Input_KeyRepeat(int key);
	bool Input_MousePress(int button);
	bool Input_MouseRelease(int button);
	void Input_MousePos(double& xpos, double& ypos);

    // FONTS
    bool Fonts_Add(std::string fontKey, const char* fontPath, int fontSize);
    void Fonts_Write(std::string text, float x, float y, float scale, glm::vec3 color);
    void Fonts_Clear();

};

#endif // ENGINE_HPP
