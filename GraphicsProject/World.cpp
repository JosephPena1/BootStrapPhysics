#include "World.h"
#include "glm/ext.hpp"

World::World(int width, int height)
{
	m_width = width;
	m_height = height;
}

void World::start()
{
	//Initialize the quad
	//m_quad.setTransform(glm::mat4(10.0f));
	m_quad.start();

	//Create camera transforms
	m_camera.setTransform(glm::lookAt(
		glm::vec3(5, 5, 5),
		glm::vec3(0),
		glm::vec3(0, 1, 0))
	);

	m_projectionMatrix = glm::perspective(
		m_camera.getFieldOfView() * glm::pi<float>() / 180.0f,
		(float)m_width / (float)m_height,
		m_camera.getNearClip(),
		m_camera.getFarClip()
	);
}

void World::update(float deltaTime)
{

}

void World::draw(aie::ShaderProgram* shader)
{
	m_quad.draw(shader);
}

void World::end()
{

}

glm::mat4 World::getProjectionView()
{
	return m_projectionMatrix * m_camera.getTransform();
}
