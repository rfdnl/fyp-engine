#ifndef TEST_GAME_HPP
#define TEST_GAME_HPP

#include "Subsystem/Test/TestBase.hpp"
#include "Subsystem/Game.hpp"

class TestGame : public Game
{
private:
	TestBase* currentTest;
	TestMenu* testMenu;
	void Init();
	void Start();
	void Update(std::chrono::duration<double> deltaTime);
	void Draw();
	void ImGuiDraw() override;
	void End();
public:
	TestGame();
};

#endif // TEST_GAME_HPP
