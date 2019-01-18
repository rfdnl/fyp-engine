#include "GameObject.hpp"

GameObject::GameObject()
:
position(0.0f), size(1.0f),
velocity(0.0f), rgba(1.0f),
rotation(0.0f), texture(),
isSolid(false), destroyed(false)
{
	//
}

GameObject::GameObject(
	glm::vec3 position,
	glm::vec2 size,
	Texture texture,
	glm::vec4 rgba,
	glm::vec2 velocity)
:
	position(position), size(size),
	velocity(velocity), rgba(rgba),
	rotation(0.0f), texture(texture),
	isSolid(false), destroyed(false)
{
	//
}

void GameObject::Draw(Engine& engine){
	engine.Render_Draw(texture, position, size, rotation, rgba);
}
