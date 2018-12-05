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
    graphics.Create("Window title", 800, 450, 50, 50);
    audio.NewSource("test");
    audio.NewBuffer("tick", "audio/tick.wav");
	if (audio.CanPlay("test")) audio.Play("test", "tick");
    //texture = graphics.NewTexture("images/test.png");
}

void Engine::InputProcessing(){
    graphics.PollEvents();
}

void Engine::Update(std::chrono::duration<double> deltaTime){
	//
}

void Engine::Draw(){
	//graphics.Draw(texture);
    graphics.Draw();
}

void Engine::Exit(){
    running = false;
}

void Engine::End(){
	INFO("End()");
    graphics.Close();
    fonts.Clear();
    audio.End();
}

// AUDIO
void Engine::Audio_NewSource(std::string sourceKey){
	audio.NewSource(sourceKey);
}

bool Engine::Audio_NewBuffer(std::string audioKey, const char* filePath){
	return audio.NewBuffer(audioKey, filePath);
}

void Engine::Audio_Play(std::string sourceKey, std::string audioKey){
	audio.Play(sourceKey, audioKey);
}

bool Engine::Audio_CanPlay(std::string sourceKey){
	return audio.CanPlay(sourceKey);
}

// GRAPHICS
std::shared_ptr<Texture> Engine::Graphics_NewTexture(const char* filePath){
	return graphics.NewTexture(filePath);
}

void Engine::Graphics_Draw(std::shared_ptr<Texture> texture){
	graphics.Draw(texture);
}

// FONT
bool Engine::Fonts_Add(std::string fontKey, const char* fontPath, int fontSize){
	return fonts.Add(fontKey, fontPath, fontSize);
}

