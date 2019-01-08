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
    graphics.Create("Window title", 960, 540, 100, 100);
    fonts.Add("Arial20", "fonts/arial.ttf", 20);
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
void Engine::Graphics_SetBackgroundColor(float red, float green, float blue, float alpha){
	graphics.SetClearColor(red, green, blue, alpha);
}

void Engine::Graphics_ClearColor(){
	graphics.ClearColor();
}

void Engine::Graphics_ImGui_NewFrame(){
	graphics.ImGui_NewFrame();
}

void Engine::Graphics_ImGui_Draw(){
	graphics.ImGui_Draw();
}

void Engine::Graphics_Flush(){
	graphics.Flush();
}

void Engine::Graphics_Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba)
{
	graphics.Draw(texture, translation, size, rotate, rgba);
}

void Engine::Graphics_DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	graphics.DrawRect(translation, size, rotate, rgba);
}

// FONT
bool Engine::Fonts_Add(std::string fontKey, const char* fontPath, int fontSize){
	return fonts.Add(fontKey, fontPath, fontSize);
}

