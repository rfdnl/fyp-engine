#include "Game.hpp"
#include <cmath>

bool Game::IsRunning(){
    return Engine::IsRunning() && Engine::IsOpen();
}

// first game loop, CPU: 23%
void Game::Run(){
    Engine::Initialize();
    Engine::Start();
    while(IsRunning()){
		frameStart = std::chrono::high_resolution_clock::now();
        Engine::InputProcessing();
        Engine::Update(frameMaxDuration);
        Engine::Draw();
		frameEnd = std::chrono::high_resolution_clock::now();
		deltaTime = frameEnd - frameStart;

		if (printFPStime >= std::chrono::seconds(1)){
			std::cout << std::chrono::duration_cast<std::chrono::seconds>(runTime).count() << " sec, " << frames << " fps" << std::endl;
			printFPStime -= std::chrono::seconds(1);
			frames = 0;
		}
		runTime += deltaTime;
		printFPStime += deltaTime;
		frames++;
    }
    Engine::End();
}

// second game loop: CPU : 33 %
void Game::Run2(){
    SetMaxFPS(60);
    Engine::Initialize();	// default engine's  configuration
    this->Init();		// allow developer to change engine's configuration
    Engine::Start();	// load default contents
    this->Start();	// allow developer to load contents

    frameStart = std::chrono::high_resolution_clock::now();
    while(IsRunning()){
		frameEnd = std::chrono::high_resolution_clock::now();
		deltaTime = frameEnd - frameStart;
		frameStart = frameEnd;
		frameDuration += deltaTime;

		while(frameDuration >= frameMaxDuration){
			Engine::InputProcessing(); // store input flags
			Engine::Update(frameMaxDuration); // update engine
			this->Update(frameMaxDuration);
			this->Draw(); // allow developer to determine what to be drawn
			Engine::Draw(); // draw all
			frameDuration -= frameMaxDuration;
			frames++;

		}

		if (printFPStime >= std::chrono::seconds(1)){
			std::cout << std::chrono::duration_cast<std::chrono::seconds>(runTime).count() << " sec, " << frames << " fps" << std::endl;
			printFPStime -= std::chrono::seconds(1);
			frames = 0;
		}

		runTime += deltaTime;
		printFPStime += deltaTime;
    }
    this->End(); // allow developer to do anything before release the engine
    Engine::End(); // release the engine
}

void Game::SetMaxFPS(int n){
	// 1 frame period in millisecond
	double framePeriodMs = (1.0 / (double)n) * 1000.0;
	// ceiling and convert to integer
	int framePeriodi = std::ceil(framePeriodMs);
	frameMaxDuration = std::chrono::milliseconds(framePeriodi);
}
