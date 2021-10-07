#include "Mesh.h"

Mesh::Mesh()
{
	m_transform = 
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	m_triCount = 0;
	m_vertexArrayObject = 0;
	m_vertexBufferObject = 0;
	m_indexBufferObject = 0;
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_vertexArrayObject);
	glDeleteBuffers(1, &m_vertexBufferObject);
	glDeleteBuffers(1, &m_indexBufferObject);
}

void Mesh::start()
{
	assert(m_vertexArrayObject == 0);

	//Generate buffers and array
	glGenBuffers(1, &m_vertexBufferObject);
	glGenVertexArrays(1, &m_vertexArrayObject);

	//Bind vertex array and vertex buffer
	glBindVertexArray(m_vertexArrayObject);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);

	//Generate the vertices
	unsigned int vertexCount;
	Vertex* vertices = generateVertices(vertexCount, m_triCount);

	//Fill vertex buffer
	glBufferData(
		GL_ARRAY_BUFFER,	//Type of buffer
		sizeof(Vertex) * vertexCount,	//Size of bytes of all vertices
		vertices,			//All vertices
		GL_STATIC_DRAW		//How the data will update
	);

	//A variable to hold the memory position
	unsigned int memoryPos = 0u;
	//Enable vertex [POSITION] as first attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,					//Attribute index
		4,					//Number of values within attribute
		GL_FLOAT,			//Type of each value
		GL_FALSE,			//Wether to normalize
		sizeof(Vertex),		//Size in bytes of the one vertex
		(void*)memoryPos	//Memory position of this attribute
	);
	memoryPos += sizeof(Vertex::position);

	//Enable vertex [NORMAL] as second attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,					//Attribute index
		4,					//Number of values within attributes
		GL_FLOAT,			//Type of each value
		GL_TRUE,			//Wether to normalize
		sizeof(Vertex),		//Size in bytes of one vertex
		(void*)memoryPos	//Memory position of this attribute
	);
	memoryPos += sizeof(Vertex::normal);

	//Enable vertex [TEXTURE COORDINATE] as third attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,					//Attribute index
		2,					//Number of values within attributes
		GL_FLOAT,			//Type of each value
		GL_FALSE,			//Wether to normalize
		sizeof(Vertex),		//Size in bytes of one vertex
		(void*)memoryPos	//Memory position of this attribute
	);
	memoryPos += sizeof(Vertex::texCoord);

	//Enable vertex [TANGENT] as fourth attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(
		3,					//Attribute index
		4,					//Number of values within attributes
		GL_FLOAT,			//Type of each value
		GL_FALSE,			//Wether to normalize
		sizeof(Vertex),		//Size in bytes of one vertex
		(void*)memoryPos	//Memory position of this attribute
	);
	memoryPos += sizeof(Vertex::tangent);

	//Enable vertex [COLOR] as fifth attribute
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(
		4,					//Attribute index
		4,					//Number of values within attributes
		GL_FLOAT,			//Type of each value
		GL_FALSE,			//Wether to normalize
		sizeof(Vertex),		//Size in bytes of one vertex
		(void*)memoryPos	//Memory position of this attribute
	);
	memoryPos += sizeof(Vertex::color);

	//Unbind buffer and array
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Deallocate memory
	delete[] vertices;
}

void Mesh::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("modelMatrix", m_transform);
	glBindVertexArray(m_vertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, m_triCount * 3);
}
