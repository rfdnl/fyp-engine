#ifndef BREAKOUT_BALL_HPP
#define BREAKOUT_BALL_HPP

#include "GameObject.hpp"

class BreakoutBall : public GameObject {
public:
	float radius;
	bool stuck;
	BreakoutBall();
	BreakoutBall(
		glm::vec3 position,
		float radius,
		glm::vec2 velocity,
		Texture texture);
	glm::vec3 Move(float dt, unsigned int windowWidth, unsigned int windowHeight);
	void Reset(glm::vec3 position, glm::vec2 velocity);
};

#endif // BREAKOUT_BALL_HPP
