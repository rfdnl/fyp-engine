#include "Game.hpp"
#include <cmath>

bool Game::IsRunning(){
    return engine.IsRunning() && engine.IsOpen();
}

// first game loop, CPU: 23%
void Game::Run(){
    _Init();
    _Start();
    while(IsRunning()){
		frameStart = std::chrono::high_resolution_clock::now();
        _InputProcessing();
        _Update();
        _Draw();
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
    _End();
}

// second game loop: CPU : 33 %
void Game::Run2(){
    SetMaxFPS(60);
    _Init();	// default engine's  configuration
    Init();		// allow developer to change engine's configuration
    _Start();	// load default contents
    Start();	// allow developer to load contents

    frameStart = std::chrono::high_resolution_clock::now();
    while(IsRunning()){
		frameEnd = std::chrono::high_resolution_clock::now();
		deltaTime = frameEnd - frameStart;
		frameStart = frameEnd;

		_InputProcessing(); // store input flags

		frameDuration += deltaTime;
		while(frameDuration >= frameMaxDuration){
			_Update(); // update engine
			Update(frameMaxDuration);
			Draw(); // allow developer to determine what to be drawn
			_Draw(); // draw all
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
    End();
    _End();
}

void Game::_Init(){
    engine.Initialize();
}

void Game::_Start(){
    engine.Start();
}

void Game::_InputProcessing(){
    engine.InputProcessing();
}

void Game::_Update(){
    engine.Update(frameMaxDuration);
}

void Game::_Draw(){
    engine.Draw();
}

void Game::_End(){
    engine.End();
}

void Game::SetMaxFPS(int n){
	// 1 frame period in millisecond
	double framePeriodMs = (1.0 / (double)n) * 1000.0;
	// ceiling and convert to integer
	int framePeriodi = std::ceil(framePeriodMs);
	frameMaxDuration = std::chrono::milliseconds(framePeriodi);
}
