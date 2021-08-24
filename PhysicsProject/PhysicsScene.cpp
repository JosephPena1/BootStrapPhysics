#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Sphere.h"
#include "Plane.h"
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

		checkCollision();
	}
}

void PhysicsScene::draw()
{
	for (PhysicsObject* actor : m_actors)
		actor->draw();
}

//Collision function pointer type
typedef bool(*collisionCheckFn)(PhysicsObject*, PhysicsObject*);

//Array of collision functions
static collisionCheckFn collisionFunctionArray[] = {
	PhysicsScene::planeToPlane,PhysicsScene::planeToSphere,PhysicsScene::planeToBox,
	PhysicsScene::sphereToPlane,PhysicsScene::sphereToSphere,PhysicsScene::sphereToBox,
	PhysicsScene::boxToPlane,PhysicsScene::boxToSphere,PhysicsScene::boxToBox
};

//Checks collision for each actor in the scene
void PhysicsScene::checkCollision()
{
	//Check each actor for a collision
	auto outerEnd = m_actors.end();
	outerEnd--;
	for (auto outer = m_actors.begin(); outer != outerEnd; outer++)
	{
		auto innerStart = outer;
		innerStart++;
		for (auto inner = innerStart; inner != m_actors.end(); inner++)
		{
			//Get the physics objects
			PhysicsObject* object1 = *outer;
			PhysicsObject* object2 = *inner;

			int shapeId1 = (int)(object1->getShapeID());
			int shapeId2 = (int)(object2->getShapeID());

			//i = (y * w) + x
			int i = (shapeId1 * (int)ShapeType::LENGTH) + shapeId2;
			//Retreive and call the collision check from the array
			collisionCheckFn collisionFuntionPtr = collisionFunctionArray[i];
			if (collisionFuntionPtr != nullptr)
				collisionFuntionPtr(object1, object2);
		}
	}
}

bool PhysicsScene::planeToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	return false;
}

bool PhysicsScene::planeToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	return sphereToPlane(object2, object1);
}

bool PhysicsScene::planeToBox(PhysicsObject* object1, PhysicsObject* object2)
{

	return false;
}

bool PhysicsScene::sphereToPlane(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere = dynamic_cast<Sphere*>(object1);
	Plane* plane = dynamic_cast<Plane*>(object2);

	if (sphere && plane)
	{
		//D1 = (C dot N) - D - R
		//D1: Distance from the sphere surface to the plane surface
		//C: Center of the sphere
		//N: Normal of the plane
		//D: Distance from the plane to the origin
		//R: Radius of the sphere
		glm::vec2 sphereCenter = sphere->getPosition(); //C
		glm::vec2 planeNormal = plane->getNormal();		//N
		float planeDistance = plane->getDistance();		//D
		float sphereRadius = sphere->getRadius();		//R
		float sphereToPlaneDistance = glm::dot(sphereCenter, planeNormal) - planeDistance - sphereRadius;

		if (sphereToPlaneDistance <= 0)
		{
			sphere->applyForce(-(sphere->getVelocity() * sphere->getMass()));
			return true;
		}
	}

	return false;
}

bool PhysicsScene::sphereToSphere(PhysicsObject* object1, PhysicsObject* object2)
{
	Sphere* sphere1 = dynamic_cast<Sphere*>(object1);
	Sphere* sphere2 = dynamic_cast<Sphere*>(object2);

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

bool PhysicsScene::sphereToBox(PhysicsObject* object1, PhysicsObject* object2)
{

	return false;
}

bool PhysicsScene::boxToPlane(PhysicsObject* object1, PhysicsObject* object2)
{

	return false;
}

bool PhysicsScene::boxToSphere(PhysicsObject* object1, PhysicsObject* object2)
{

	return false;
}

bool PhysicsScene::boxToBox(PhysicsObject* object1, PhysicsObject* object2)
{

	return false;
}
