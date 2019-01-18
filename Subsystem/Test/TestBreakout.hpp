#ifndef TEST_BREAKOUT_HPP
#define TEST_BREAKOUT_HPP

#include "../Component/Level/BreakoutLevel.hpp"
#include "../Component/Level/BreakoutBall.hpp"
#include "../Component/Graphics/Texture.hpp"
#include "../Global.hpp"
#include "../Component/Input/Keyboard.hpp"
#include "TestBase.hpp"
#include <memory>
#include <tuple>

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

typedef std::tuple<bool, Direction, glm::vec2> Collision;
const glm::vec2 PLAYER_SIZE(100, 20);
const GLfloat PLAYER_VELOCITY(500.0f);
const glm::vec2 INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const GLfloat BALL_RADIUS = 12.5f;

class TestBreakout : public TestBase
{
	Texture background;
	Texture cat;
	Texture star;
	std::shared_ptr<GameObject> player;
	std::shared_ptr<BreakoutBall> ball;
	BreakoutLevel level;
public:
	TestBreakout(Engine& engine);
	~TestBreakout();
	void Update(std::chrono::duration<double> deltaTime) override;
	void Draw() override;
	void ImGuiDraw() override;

	void OnCollision();

	bool CheckCollision(GameObject& a, GameObject& b);
	Collision CheckCollision(BreakoutBall& a, GameObject& b);
	Direction VectorDirection(glm::vec2 nearest);

	void ResetLevel();
	void ResetPlayer();

};

#endif // TEST_BREAKOUT_HPP
