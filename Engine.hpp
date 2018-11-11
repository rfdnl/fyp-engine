#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include <iostream>
#include <chrono>
#include "ILoggable.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"

class Engine : public ILoggable
{
    Fonts fonts;
    Graphics graphics;
    static bool running;
public:
    Engine(std::shared_ptr<Logger> logPtr):
        ILoggable(logPtr, "Engine"),
        fonts(logPtr),
        graphics(logPtr)
    {}
    static bool IsRunning();
    bool ShouldClose();
    bool Initialize();
    void Start();
    void InputProcessing();
    void Update(std::chrono::duration<double> deltaTime);
    void Draw();
    static void Exit();
    void End();
};

#endif // ENGINE_HPP
