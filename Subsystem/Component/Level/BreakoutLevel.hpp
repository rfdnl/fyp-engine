#ifndef BREAKOUT_LEVEL_HPP
#define BREAKOUT_LEVEL_HPP

#include <fstream>
#include <sstream>
#include <vector>
#include <glm/glm.hpp>
#include "GameObject.hpp"
#include "../../Engine.hpp"

class BreakoutLevel {
	Texture brickTexture;
public:
	std::vector<GameObject> bricks;
	BreakoutLevel() { }
	void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
	void Draw(Engine& engine);
	bool IsCompleted();
	void Close();
private:
	void Init(std::vector<std::vector<unsigned int>> tileData,
		unsigned int levelWidth,
		unsigned int levelHeight);
};

#endif // BREAKOUT_LEVEL_HPP
