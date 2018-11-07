#include "Game.hpp"
#include "Engine.hpp"
#include <chrono>
#include <iostream>

Game::Game(){
    engine = new Engine();
}

bool Game::IsRunning(){
    return !engine->ShouldClose();
}

void Game::Run(){
    PreInit();
    Init();
    Start();
    while(Engine::IsRunning()){
        InputProcessing();
        Update();
        Draw();
    }
    End();
}

void Game::PreInit(){
    engine->Init();
}

void Game::Init(){
    // window configuration
    // load fonts, textures, etc.
}

void Game::Start(){
    engine->Start();
}

void Game::FrameStart(){
    frameStart = std::chrono::high_resolution_clock::now();
}

void Game::InputProcessing(){
    FrameStart();
    engine->InputProcessing();
}

void Game::Update(){
    engine->Update(deltaTime);
    CalculateFPS();
}

void Game::CalculateFPS(){
    if (printFpsTime >= std::chrono::seconds(1)){
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(runTime).count() << " sec, " << frames << " fps" << std::endl;
        printFpsTime -= std::chrono::seconds(1);
        frames = 0;
    }

    printFpsTime += deltaTime;
    runTime += deltaTime;
    frames++;
}

void Game::Draw(){
    engine->Draw();
    FrameEnd();
}

void Game::FrameEnd(){
    frameEnd = std::chrono::high_resolution_clock::now();
    deltaTime = frameEnd - frameStart;
}

void Game::End(){
    engine->End();
    delete engine;
}
