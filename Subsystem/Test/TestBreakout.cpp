#include "TestBreakout.hpp"

TestBreakout::TestBreakout(Engine& engine):TestBase(engine){
	cat.Init("images/cat.png");
	star.Init("images/star.png");
	player = std::make_shared<GameObject>(
		glm::vec3( // position
			(Global::ScreenWidth() / 2) - cat.Width() / 2,
			Global::ScreenHeight() - cat.Height(),
			0.0f),
		glm::vec2( // size
			cat.Width(),
			cat.Height()),
		cat); // texture

	ball = std::make_shared<BreakoutBall>(
		glm::vec3( // position
			player->position.x,
			player->position.y,
			0.0f),
		12.5f, // radius
		INITIAL_BALL_VELOCITY, // velocity
		star); // texture

	background.Init("images/bg.png");
	level.Load("levels/level.txt", Global::ScreenWidth(), Global::ScreenHeight());
}

TestBreakout::~TestBreakout(){
	background.Close();
	cat.Close();
	level.Close();
}

void TestBreakout::Update(std::chrono::duration<double> deltaTime) {
	float velocity = 300.0f * deltaTime.count();

	// input
	if (engine.Input_KeyPress(Keyboard::A) || engine.Input_KeyRepeat(Keyboard::A)){
		if (player->position.x > 0){
			player->position.x -= velocity;
			if (ball->stuck){
				ball->position.x -= velocity;
			}
		}
	}

	if (engine.Input_KeyPress(Keyboard::D) || engine.Input_KeyRepeat(Keyboard::D)){
		if (player->position.x < Global::ScreenWidth() - player->size.x){
			player->position.x += velocity;
			if (ball->stuck){
				ball->position.x += velocity;
			}
		}
	}

	if (engine.Input_KeyPress(Keyboard::Space)){
		ball->stuck = false;
	}

	// update
	ball->Move(deltaTime.count(), Global::ScreenWidth(), Global::ScreenHeight());

	// postupdate (collision)
	OnCollision();

	// win lose condition
	if (ball->position.y >= Global::ScreenHeight()){
		engine.Audio_Play("test", "explode");
		ResetLevel();
		ResetPlayer();
	}
}

void TestBreakout::Draw(){
	engine.Render_Draw(background, glm::vec3(0.0f), glm::vec2(Global::ScreenWidth(), Global::ScreenHeight()));
	level.Draw(engine);
	player->Draw(engine);
	ball->Draw(engine);
}

void TestBreakout::ResetLevel(){
	level.Close();
	level.Load("levels/level.txt", Global::ScreenWidth(), Global::ScreenHeight());
}

void TestBreakout::ResetPlayer(){
	player->position = glm::vec3( // position
			(Global::ScreenWidth() / 2) - cat.Width() / 2,
			Global::ScreenHeight() - cat.Height(),
			0.0f);
	ball->Reset(glm::vec3( // position
			player->position.x,
			player->position.y,
			0.0f),
			INITIAL_BALL_VELOCITY); // velocity
}

void TestBreakout::OnCollision(){
	for (GameObject &brick : level.bricks){
		if (!brick.destroyed){
			Collision collision = CheckCollision(*ball, brick);
			if (std::get<0>(collision)){
				brick.destroyed = true;

				// play audio here
				engine.Audio_Play("test", "tick");

				Direction dir = std::get<1>(collision);
				glm::vec2 difference = std::get<2>(collision);
				if (dir == LEFT || dir == RIGHT){ // horizontal
					ball->velocity.x = -ball->velocity.x; // switch
					float penetration = ball->radius - std::abs(difference.x);
					if (dir == LEFT){
						ball->position.x += penetration; // up
					} else {
						ball->position.x -= penetration; // down
					}
				} else {	// vertical
					ball->velocity.y = -ball->velocity.y; // switch
					float penetration = ball->radius - std::abs(difference.y);
					if (dir == UP){
						ball->position.y += penetration; // up
					} else {
						ball->position.y -= penetration; // down
					}
				}
			}
		}

		// check collision of star with cat
		Collision result = CheckCollision(*ball, *player);
		if (!ball->stuck && std::get<0>(result)){
			// check where it hit the cat
			float centerBoard = player->position.x + player->size.x / 2;
			float distance = (ball->position.x + ball->radius) - centerBoard;
			float percentage = distance / (player->size.x / 2);

			// move accordingly
			float strength = 2.0f;
			glm::vec2 oldVelocity = ball->velocity;
			ball->velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
			ball->velocity = glm::normalize(ball->velocity) * glm::length(oldVelocity);
			ball->velocity.y = -1 * abs(ball->velocity.y);
		}
	}
}

bool TestBreakout::CheckCollision(GameObject &one, GameObject &two){ // AABB - AABB collision
	bool collisionX = one.position.x + one.size.x >= two.position.x &&
		two.position.x + two.size.x >= one.position.x;
	bool collisionY = one.position.y + one.size.y >= two.position.y &&
		two.position.y + two.size.y >= one.position.y;
	return collisionX && collisionY;
}

Collision TestBreakout::CheckCollision(BreakoutBall& ball, GameObject& two){ // AABB - Circle collision
	glm::vec2 center(ball.position + ball.radius);
	// get AABB info (center, half-extents)
	glm::vec2 aabbHalfExtents(two.size.x / 2, two.size.y / 2);
	glm::vec2 aabbCenter(two.position.x + aabbHalfExtents.x, two.position.y + aabbHalfExtents.y);

	glm::vec2 difference = center - aabbCenter;
	glm::vec2 clamped = glm::clamp(difference, -aabbHalfExtents, aabbHalfExtents);
	// get nearest position of bricks to star
	glm::vec2 nearest = aabbCenter + clamped;
	difference = nearest - center;

	if (glm::length(difference) < ball.radius){
		return std::make_tuple(true, VectorDirection(difference), difference);
	} else {
		return std::make_tuple(false, DOWN, glm::vec2(0, 0));
	}
}

Direction TestBreakout::VectorDirection(glm::vec2 target){
	glm::vec2 dirs[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };

    float max = 0.0f;
    unsigned int bestMatch = -1;
    for(unsigned int i = 0; i < 4; i++){
		float dotProd = glm::dot(glm::normalize(target), dirs[i]);
		if (dotProd > max){
			max = dotProd;
			bestMatch = i;
		}
    }
    return (Direction)bestMatch;
}

void TestBreakout::ImGuiDraw(){
	//
}
