#pragma once
#include "Entity.h"
#include "gl_core_4_4.h"
#include "glm\vec4.hpp"
#include "glm\mat4x4.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class Mesh : public Entity
{
public:
	Mesh();
	~Mesh();

	void start() override;
	void draw() override;

	virtual Vertex* generateVertices(unsigned int& vertexCount, unsigned int& triCount) = 0;

	glm::mat4 getTransform() { return m_transform; }
	void setTransform(glm::mat4 transform) { m_transform = transform; }

private:
	glm::mat4 m_transform;
	unsigned int m_triCount, m_vertexArrayObject,
		m_vertexBufferObject, m_indexBufferObject;
};
