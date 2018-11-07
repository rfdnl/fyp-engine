#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "Fonts.hpp"
#include "Graphics.hpp"
#include "Logger.hpp"
#include "ILoggable.hpp"
#include <chrono>       // timer manipulation

class Engine : public ILoggable
{
    Fonts* fonts;
    Graphics* graphics;
    static bool running;
    std::string CLASS_NAME = "Engine.cpp";
public:
    Engine();
    static bool IsRunning();
    bool ShouldClose();
    bool Init();
    void Start();
    void InputProcessing();
    void Update(std::chrono::duration<double> deltaTime);
    void Draw();
    static void Exit();
    void End();
};

#endif // ENGINE_HPP
