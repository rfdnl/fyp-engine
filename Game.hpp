#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include "Engine.hpp"

class Game{
    Engine engine;
    std::chrono::duration<double> printFPStime, runTime, deltaTime;
    std::chrono::high_resolution_clock::time_point frameStart, frameEnd;
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
    bool IsRunning();
public:
    Game():
        engine(std::make_shared<Logger>("log.txt")),
        printFPStime(std::chrono::duration<double>::zero()),
        runTime(std::chrono::duration<double>::zero()),
        deltaTime(std::chrono::duration<double>::zero())
    {
        std::cout << "Game()" << std::endl;
    }

    ~Game(){
        std::cout << "~Game()" << std::endl;
    }

    void Run();
};

#endif // GAME_HPP
