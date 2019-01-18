#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include "../Graphics/Texture.hpp"
#include "../../Engine.hpp"
#include <glm/glm.hpp>

class GameObject {
public:
	glm::vec3 position;
	glm::vec2 size, velocity;
	glm::vec4 rgba;
	float rotation;
	Texture texture;
	bool isSolid;
	bool destroyed;

	GameObject();
	GameObject(
		glm::vec3 position,
		glm::vec2 size,
		Texture texture,
		glm::vec4 rgba = glm::vec4(1.0f),
		glm::vec2 velocity = glm::vec2(0.0f));
	virtual void Draw(Engine& engine);
};

#endif // GAME_OBJECT_HPP
