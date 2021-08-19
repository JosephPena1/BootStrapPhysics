#include "PhysicsScene.h"
#include "PhysicsObject.h"

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{

}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.insert(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	m_actors.erase(actor);
}

void PhysicsScene::update(float deltaTime)
{
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	//If accumalated Time is greater than timeStep
	while (accumulatedTime >= m_timeStep)
	{
		//Call each actor's fixed update
		for (PhysicsObject* actor : m_actors)
			actor->fixedUpdate(m_gravity, m_timeStep);

		accumulatedTime -= m_timeStep;
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}