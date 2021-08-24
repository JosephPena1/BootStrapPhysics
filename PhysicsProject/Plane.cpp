#include "Plane.h"
#include "Gizmos.h"
#include <glm/ext.hpp>
#include "RigidBody.h"

Plane::Plane(glm::vec2 normal, float distance, glm::vec4 color) : PhysicsObject(ShapeType::PLANE)
{
	m_normal = glm::normalize(normal);
	m_distance = distance;
	m_color = color;
}

Plane::~Plane()
{

}

void Plane::fixedUpdate(glm::vec2 gravity, float timeStep)
{

}

void Plane::draw()
{
	float lineSegmentLength = 300.0f;
	glm::vec2 centerPoint = m_normal * m_distance;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	
	glm::vec2 start = centerPoint + (parallel * lineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * lineSegmentLength);

	aie::Gizmos::add2DLine(start, end, m_color);
}

void Plane::resolveCollision(RigidBody* other)
{
	//j = ((-(1 + e) * Vrel) dot n) / (n dot (n * (1 / MA + 1 / MB)))
	//j: Impulse magnitude
	//e: Coefficient of elasticity
	//Vrel: Relative velocity before the collision
	//n: Collision normal
	//M: Mass of object

	//e
	float elasticity = 1.0f;
	//Vrel
	glm::vec2 relativeVelocity = other->getVelocity() - 0.0f;
	//n
	glm::vec2 collisionNormal = getNormal();
	//MA
	float mass = other->getMass();

	//j
	float impulse = glm::dot((-(1 + elasticity) * relativeVelocity), collisionNormal)
		/ glm::dot(collisionNormal, (collisionNormal * (1 / mass)));

	other->applyForce(collisionNormal * impulse);
}
