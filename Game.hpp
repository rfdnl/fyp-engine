#ifndef GAME_HPP
#define GAME_HPP
#include "Engine.hpp"
#include <chrono>
class Game
{
    std::chrono::duration<double> printFpsTime, runTime, deltaTime;
    std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
    Engine* engine;
    int frames = 0;
    float fps = 0.0f;

    void FrameStart();
    void CalculateFPS();
    void FrameEnd();
    void PreInit();
    void Init();
    void Start();
    void InputProcessing();
    void Update();
    void Draw();
    void End();
public:
    Game();
    bool IsRunning();
    void Run();
};

#endif // GAME_HPP
