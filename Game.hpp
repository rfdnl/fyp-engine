#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include "Engine.hpp"

class Game{
private:
    std::chrono::duration<double> printFPStime, runTime, deltaTime, frameMaxDuration, frameDuration;
    std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
    int frames = 0;
    float fps = 0.0f;
    Engine engine;

    void CalculateFPS();
    bool IsRunning();
    void _PreInit();
    void _Init();
    void _Start();
    void _InputProcessing();
    void _Update();
    void _Draw();
    void _End();
protected:
    virtual void Init() = 0;
    virtual void Start() = 0;
    virtual void Update(std::chrono::duration<double> deltaTime) = 0;
    virtual void Draw() = 0;
    virtual void End() = 0;
    void SetMaxFPS(int n);
public:
    Game():
        printFPStime(std::chrono::duration<double>::zero()),
        runTime(std::chrono::duration<double>::zero()),
        deltaTime(std::chrono::duration<double>::zero()),
        frameMaxDuration(std::chrono::duration<double>::zero()),
        frameDuration(std::chrono::duration<double>::zero()),
        engine(std::make_shared<Logger>("log.txt"))
    {
        std::cout << "Game()" << std::endl;
    }

    ~Game(){
        std::cout << "~Game()" << std::endl;
    }

    void Run();
    void Run2();
};

#endif // GAME_HPP
