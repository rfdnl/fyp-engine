#include "BreakoutLevel.hpp"

void BreakoutLevel::Load(const char* file,
	unsigned int levelWidth,
	unsigned int levelHeight){
	bricks.clear();
	unsigned int tileCode;
	BreakoutLevel level;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> tileData;
	if (fstream){
		while (std::getline(fstream, line)){
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> tileCode){
				row.push_back(tileCode);
			}
			tileData.push_back(row);
		}
		if (tileData.size() > 0){
			this->Init(tileData, levelWidth, levelHeight);
		}
	}
}

void BreakoutLevel::Draw(Engine& engine){
	for(GameObject &tile : this->bricks){
		if (!tile.destroyed){
			tile.Draw(engine);
		}
	}
}

bool BreakoutLevel::IsCompleted(){
	for(GameObject &tile : this->bricks){
		if (!tile.isSolid && !tile.destroyed){
			return false;
		}
	}
	return true;
}

void BreakoutLevel::Init(std::vector<std::vector<unsigned int>> tileData,
	unsigned int levelWidth,
	unsigned int levelHeight){
	unsigned int height = tileData.size();
	unsigned int width = tileData[0].size();
	float unit_width = levelWidth / static_cast<float>(width),
		unit_height = levelHeight / static_cast<float>(height);

	brickTexture.Init("images/brick.png");

	for(unsigned int y = 0; y < height; ++y){
		for(unsigned int x = 0; x < width; ++x){
			if (tileData[y][x] > 0){ // bricks
				glm::vec3 pos(unit_width * x, unit_height * y, 0.0f);
				glm::vec2 size(unit_width, unit_height);
				GameObject brick(pos, size, brickTexture);
				brick.isSolid = true;
				bricks.push_back(brick);
			}
		}
	}
}

void BreakoutLevel::Close(){
	brickTexture.Close();
}
