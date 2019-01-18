#include "BreakoutBall.hpp"

BreakoutBall::BreakoutBall()
: GameObject(), radius(12.5f), stuck(true)
{
	//
}

BreakoutBall::BreakoutBall(
	glm::vec3 position,
	float radius,
	glm::vec2 velocity,
	Texture texture)
:
	GameObject(
		position,
		glm::vec2(radius * 2, radius * 2),
		texture,
		glm::vec4(1.0f),
		velocity),
	radius(radius),
	stuck(true)
{
	//
}

glm::vec3 BreakoutBall::Move(
	float dt,
	unsigned int windowWidth,
	unsigned int windowHeight
){
	if (!stuck){
		position += glm::vec3(velocity, 0.0f) * dt;

		if (position.x <= 0.0f){
			velocity.x = -velocity.x;
			position.x = 0.0f;
		} else if (position.x + size.x >= windowWidth){
			velocity.x = -velocity.x;
			position.x = windowWidth - size.x;
		}

		if (position.y <= 0.0f){// || position.y >= windowHeight - size.y){
			velocity.y = -velocity.y;
		}
	}
	return position;
}

void BreakoutBall::Reset(
	glm::vec3 position,
	glm::vec2 velocity
){
	this->position = position;
	this->velocity = velocity;
	this->stuck = true;
}
