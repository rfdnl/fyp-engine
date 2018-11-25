#ifndef TEST_GAME_HPP
#define TEST_GAME_HPP

#include "Game.hpp"

class TestGame : public Game
{
public:
	void Init();
	void Start();
	void Update(std::chrono::duration<double> deltaTime);
	void Draw();
	void End();
};

#endif // TEST_GAME_HPP
