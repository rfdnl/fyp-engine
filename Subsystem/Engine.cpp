#include "Engine.hpp"
#include <iostream>

Engine::Engine(std::shared_ptr<Logger> logPtr):
	ILoggable(logPtr, "Engine"),
	graphics(logPtr),
	fonts(logPtr),
	audio(logPtr)
{}

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
    renderer.Init();
	fonts.Add("Arial20", "fonts/arial.ttf", 20);
    audio.NewSource("test");
    audio.NewBuffer("tick", "audio/tick.wav");
    audio.NewBuffer("tweak", "audio/tweak.wav");
    audio.NewBuffer("explode", "audio/explode.wav");
	//if (audio.CanPlay("test")) audio.Play("test", "tick");
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
	renderer.Close();
    fonts.Clear();
    audio.End();
    graphics.Close();
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

void Engine::Render_Draw(const Texture& texture, glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	renderer.Draw(texture, translation, size, rotate, rgba);
}

void Engine::Render_DrawRect(glm::vec3 translation, glm::vec2 size, float rotate, glm::vec4 rgba){
	renderer.DrawRect(translation, size, rotate, rgba);
}

// INPUT
void Engine::Input_DEBUG(bool on){
	Input::DEBUG = on;
}

bool Engine::Input_KeyPress(int key){
	return Input::KeyPress(key);
}

bool Engine::Input_KeyRelease(int key){
	return Input::KeyRelease(key);
}

bool Engine::Input_KeyRepeat(int key){
	return Input::KeyRepeat(key);
}

bool Engine::Input_MousePress(int button){
	return Input::MousePress(button);
}

bool Engine::Input_MouseRelease(int button){
	return Input::MouseRelease(button);
}

void Engine::Input_MousePos(double& xpos, double& ypos){
	Input::MousePos(xpos, ypos);
}

// FONT
bool Engine::Fonts_Add(std::string fontKey, const char* fontPath, int fontSize){
	return fonts.Add(fontKey, fontPath, fontSize);
}

void Engine::Fonts_Write(std::string text, float x, float y, float scale, glm::vec3 color){
	fonts.Write(text, x, y, scale, color);
}

void Engine::Fonts_Clear(){
	fonts.Clear();
}

