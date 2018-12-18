#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include <iostream>
#include <chrono>
#include "Helper/ILoggable.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"

class Engine : public ILoggable
{
	std::shared_ptr<Texture> texture;
    bool running = true;
    Fonts fonts;
    Graphics graphics;
    Audio audio;
protected:
    Engine(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Engine"),
        fonts(logPtr),
        graphics(logPtr),
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

    // AUDIO
    void Audio_NewSource(std::string sourceKey);
    bool Audio_NewBuffer(std::string audioKey, const char* filePath);
    void Audio_Play(std::string sourceKey, std::string audioKey);
    bool Audio_CanPlay(std::string sourceKey);

    // GRAPHICS
	//std::shared_ptr<Texture> Graphics_NewTexture(const char* filePath);
	//void Graphics_Draw(std::shared_ptr<Texture> texture);

    // FONTS
    bool Fonts_Add(std::string fontKey, const char* fontPath, int fontSize);
};

#endif // ENGINE_HPP
