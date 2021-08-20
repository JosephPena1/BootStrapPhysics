#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "glm/ext.hpp"

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

		auto outerEnd = m_actors.end();
		outerEnd--;
		for (auto outer = m_actors.begin(); outer != outerEnd; outer++)
		{
			auto innerStart = outer;
			innerStart++;
			for (auto inner = innerStart; inner != m_actors.end(); inner++)
			{
				PhysicsObject* object1 = *outer;
				PhysicsObject* object2 = *inner;

				//Collision check
				sphereToSphere(dynamic_cast<Sphere*>(object1), dynamic_cast<Sphere*>(object2));
			}
		}
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}

bool PhysicsScene::sphereToSphere(Sphere* sphere1, Sphere* sphere2)
{
	if (sphere1 && sphere2)
	{
		glm::vec2 distanceVec = sphere1->getPosition() - sphere2->getPosition();
		float distance = glm::sqrt(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);
		float totalRadius = sphere1->getRadius() + sphere2->getRadius();

		if (glm::abs(distance) < totalRadius)
		{
			sphere1->applyForce(-(sphere1->getVelocity() * sphere1->getMass()));
			sphere2->applyForce(-(sphere2->getVelocity() * sphere2->getMass()));
			return true;
		}
	}

	return false;
}
