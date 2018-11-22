#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include <iostream>
#include <chrono>
#include "ILoggable.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"
#include "Audio.hpp"

class Engine : public ILoggable
{
    bool running = true;
    Fonts fonts;
    Graphics graphics;
    Audio audio;
public:
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
};

#endif // ENGINE_HPP
