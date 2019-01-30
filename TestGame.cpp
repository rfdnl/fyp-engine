#include "TestGame.hpp"

#include "Subsystem/Test/TestClearColor.hpp"
#include "Subsystem/Test/TestRect.hpp"
#include "Subsystem/Test/TestTexture.hpp"
#include "Subsystem/Test/TestInput.hpp"
#include "Subsystem/Test/TestFonts.hpp"
#include "Subsystem/Test/TestBreakout.hpp"
#include "Subsystem/Test/TestPhysics.hpp"

TestGame::TestGame()
//:color{ 0.2f, 0.3f, 0.8f, 1.0f }
{
	//
}

void TestGame::Init(){
	// change engine configuration here
}

void TestGame::Start(){
	// load contents here
	// test start
	currentTest = nullptr;
	testMenu = new TestMenu(GetEngine(), currentTest);
	currentTest = testMenu;

	testMenu->RegisterTest<TestClearColor>("Clear Color");
	testMenu->RegisterTest<TestRect>("Rectangle");
	testMenu->RegisterTest<TestTexture>("Texture");
	testMenu->RegisterTest<TestInput>("Input");
	testMenu->RegisterTest<TestFonts>("Fonts");
	testMenu->RegisterTest<TestBreakout>("Breakout");
	testMenu->RegisterTest<TestPhysics>("Physics");
	// test end
}

void TestGame::Update(std::chrono::duration<double> deltaTime){
    // update game logic here
    // test start
    if (currentTest){
		currentTest->Update(deltaTime);
    }
    // test end
}

void TestGame::Draw(){
	// draw all the object chronologically
	//Graphics_SetBackgroundColor(color[0],color[1],color[2],color[3]);
	//Graphics_ClearColor();
	if (currentTest){
		currentTest->Draw();
	}
}

void TestGame::ImGuiDraw(){
	//ImGui::ColorEdit4("Clear Color", color);
	if (currentTest){
		ImGui::Begin("Test");
		if (currentTest != testMenu && ImGui::Button("Menu")){
			delete currentTest;
			currentTest = testMenu;
			Audio_Play("test", "tick");
		}
		currentTest->ImGuiDraw();
		ImGui::End();
	}
}

void TestGame::End(){
	// release anything
}
