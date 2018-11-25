#include "Engine.hpp"
#include <iostream>

bool Engine::IsRunning(){
    return running;
}

bool Engine::IsOpen(){
    return graphics.IsOpen();
}

bool Engine::Initialize(){
    if (!graphics.Initialize()) return false;
    if (!fonts.Initialize()) return false;
    if (!audio.Initialize()) return false;
    return true;
}

void Engine::Start(){
    fonts.Add("Arial20", "fonts/arial.ttf", 20);
    graphics.Create("Window title");
    audio.NewSource("test");
    audio.NewBuffer("tick", "audio/tick.wav");
	if (audio.CanPlay("test")) audio.Play("test", "tick");
}

void Engine::InputProcessing(){
    graphics.PollEvents();
}

void Engine::Update(std::chrono::duration<double> deltaTime){
	//
}

void Engine::Draw(){
    graphics.Draw();
}

void Engine::Exit(){
    running = false;
}

void Engine::End(){
    graphics.Close();
    fonts.Clear();
    audio.End();
}
