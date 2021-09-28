#include "Mesh.h"

Mesh::Mesh()
{
	m_triCount = 0;
	m_vertexArray = 0;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;

	assert(m_vertexArray == 0);

	//Generate buffers and array
	glGenBuffers(1, &m_vertexBuffer);
	glGenVertexArrays(1, &m_vertexArray);

	//Bind vertex array and vertex buffer
	glBindVertexArray(m_vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteBuffers(1, &m_indexBuffer);
}
