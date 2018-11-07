#include "Engine.hpp"
#include "Fonts.hpp"
#include "Graphics.hpp"
#include <iostream>

bool Engine::running = true;

Engine::Engine(){
    Logger* log = new Logger();
    SetLog(log, "Engine.cpp");
    graphics = new Graphics(log);
    fonts = new Fonts(log);
}

bool Engine::IsRunning(){
    return running;
}

bool Engine::ShouldClose(){
    return graphics->ShouldClose();
}

bool Engine::Init(){
    if (!graphics->Init()) return false;
    if (!fonts->Init()) return false;
    return true;
}

void Engine::Start(){
    // load contents
    fonts->Add("Arial20", "fonts/arial.ttf", 20);
    graphics->Create("Window title", Graphics::DEFAULT_WIDTH, Graphics::DEFAULT_HEIGHT, Graphics::DEFAULT_POS, Graphics::DEFAULT_POS);
}

void Engine::InputProcessing(){
    graphics->PollEvents();
}

void Engine::Update(std::chrono::duration<double> deltaTime){
    //
}

void Engine::Draw(){
    graphics->Draw();
}

void Engine::Exit(){
    running = false;
}

void Engine::End(){
    if (running) graphics->Close();
    delete graphics;
    fonts->Clear();
    delete fonts;
    CloseLog();
}
