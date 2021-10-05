#pragma once
#include "glm/mat4x4.hpp"

class Entity
{
public:
	Entity() {}
	~Entity() {}

	virtual void start() {};
	virtual void update(float deltaTime);
	virtual void draw() {};
	virtual void end() {};

	Entity* getParent() { return m_parent; }
	void setParent(Entity* parent) { m_parent = parent; }
	glm::mat4 getLocalTransform() { return m_localTransform; }
	void setLocalTransform(glm::mat4 transform);
	glm::mat4 getGlobalTransform();

private:
	void updateGlobalTransform();

private:
	Entity* m_parent = nullptr;
	glm::mat4 m_localTransform = glm::mat4(1.0f);
	glm::mat4 m_globalTransform = glm::mat4(1.0f);
	bool isGlobalTransformDirty = true;
};
