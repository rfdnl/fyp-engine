#include "TestPhysics.hpp"
#include <iomanip>

// TODO: Box2D is in meter! OpenGL is in pixel unit! PLS FIX

TestPhysics::TestPhysics(Engine& engine)
:
TestBase(engine),
gravity(0.0f, -10.0f),
world(gravity)
{
	bodySize = glm::vec2(10.0f, 10.0f);
	groundSize = glm::vec2(Global::ScreenWidth(), 10.0f);

	groundBodyDef.position.Set(0.0f, 0.0f);
	groundBody = world.CreateBody(&groundBodyDef);
	groundBox.SetAsBox(groundSize.x / 2, groundSize.y / 2);
	groundBody->CreateFixture(&groundBox, 0.0f);

	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 50.0f);
	body = world.CreateBody(&bodyDef);
	dynamicBox.SetAsBox(bodySize.x / 2, bodySize.y / 2);

	fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 1.0f;
	body->CreateFixture(&fixtureDef);
}

void TestPhysics::Update(std::chrono::duration<double> deltaTime){
	//std::cout << "dt: " << deltaTime.count() << std::endl; // 0.017
	float timeStep = static_cast<float>(deltaTime.count());
	world.Step(timeStep, velocityIterations, positionIterations);
	std::cout << std::fixed << std::setprecision(2)
		<< "x: " << body->GetPosition().x
		<< ", y: " << body->GetPosition().y
		<< ", r: " << body->GetAngle()
	<< std::endl;
}

void TestPhysics::Draw(){
	engine.Render_DrawRect(
		glm::vec3(groundBody->GetPosition().x, groundBody->GetPosition().y, 0.0f),
		groundSize,
		groundBody->GetAngle(),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
	);
	engine.Render_DrawRect(
		glm::vec3(body->GetPosition().x, body->GetPosition().y, 0.0f),
		bodySize,
		body->GetAngle(),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
	);
}

void TestPhysics::ImGuiDraw(){
	//
}

TestPhysics::~TestPhysics(){
	//
}
