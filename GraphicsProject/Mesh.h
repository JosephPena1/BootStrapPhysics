#pragma once
#include "gl_core_4_4.h"
#include "glm/vec4.hpp"

struct Vertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void start();
	void draw();

private:
	unsigned int m_triCount, m_vertexArrayObject,
		m_vertexBufferObject, m_indexBufferObject;
};
