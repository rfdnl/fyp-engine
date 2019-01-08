#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include <iostream>
#include <chrono>
#include "Helper/ILoggable.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"
#include "Input.hpp"

class Engine : public ILoggable
{
	std::shared_ptr<Texture> texture;
    bool running = true;
    Graphics graphics;
    Fonts fonts;
    Audio audio;
protected:
    Engine(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Engine"),
        graphics(logPtr),
        fonts(logPtr),
        audio(logPtr)
    {}
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
    void Graphics_Draw(const Texture& texture, glm::vec3 translation = glm::vec3(0.0f), glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec4 rgba = glm::vec4(1.0f));
	void Graphics_DrawRect(glm::vec3 translation = glm::vec3(0.0f), glm::vec2 size = glm::vec2(10, 10), float rotate = 0.0f, glm::vec4 rgba = glm::vec4(1.0f));

	// INPUT
	void Input_DEBUG(bool on){
		Input::DEBUG = on;
	}

	bool Input_KeyPress(int key){
		return Input::KeyPress(key);
	}

	bool Input_KeyRelease(int key){
		return Input::KeyRelease(key);
	}

	bool Input_KeyRepeat(int key){
		return Input::KeyRepeat(key);
	}

	bool Input_MousePress(int button){
		return Input::MousePress(button);
	}

	bool Input_MouseRelease(int button){
		return Input::MouseRelease(button);
	}

	void Input_MousePos(double& xpos, double& ypos){
		Input::MousePos(xpos, ypos);
	}

    // FONTS
    bool Fonts_Add(std::string fontKey, const char* fontPath, int fontSize);
};

#endif // ENGINE_HPP
