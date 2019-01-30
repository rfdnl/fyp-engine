#include "TestBase.hpp"
#include <Box2D/Box2D.h>
#include "../Global.hpp"

class TestPhysics : public TestBase {

	glm::vec2 bodySize;
	glm::vec2 groundSize;
	// world
	b2Vec2 gravity;
	b2World world;

	// static body
	b2BodyDef groundBodyDef;
	b2Body* groundBody;
	b2PolygonShape groundBox;

	// dynamic body
	b2BodyDef bodyDef;
	b2Body* body;
	b2PolygonShape dynamicBox;

	// dynamic body's fixture
	b2FixtureDef fixtureDef;

	// simulation config
	int velocityIterations = 5;
	int positionIterations = 5;
public:
	TestPhysics(Engine& engine);
	void Update(std::chrono::duration<double> deltaTime) override;
	void Draw() override;
	void ImGuiDraw() override;
	~TestPhysics() override;
};
