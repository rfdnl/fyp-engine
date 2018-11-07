/*
#include <AL/al.h>      // audio library
#include <AL/alc.h>
#include <Box2D/Box2D.h>// physics library
#include <thread>       // thread manipulation
*/
#include "Game.hpp"

int main(int argc, char* args[]){
    Game* game = new Game();
    game->Run();
    delete game;
}

