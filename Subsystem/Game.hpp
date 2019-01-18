#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include "Engine.hpp"

class Game : public Engine
{
private:
    std::chrono::duration<double> printFPStime, runTime, deltaTime, frameMaxDuration, frameDuration;
    std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
    int frames = 0;
    float fps = 0.0f;

    void CalculateFPS();
    bool IsRunning();
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update(std::chrono::duration<double> deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void ImGuiDraw(){}
    virtual void End() = 0;
    void SetMaxFPS(int n);
public:
    Game();
    ~Game();

	Engine& GetEngine();
    void Run();
    void Run2();
};

#endif // GAME_HPP
