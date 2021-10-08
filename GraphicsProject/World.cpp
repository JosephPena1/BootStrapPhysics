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
	/*m_camera.setTransform(glm::lookAt(
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0),
		glm::vec3(0, 1, 0))
	);*/
	m_camera.setPosition(glm::vec3(2.0f, 2.0f, 2.0f));
	m_camera.setYaw(-135);
	m_camera.setPitch(-40);

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

void World::draw()
{
	m_quad.draw();
}

void World::end()
{

}

glm::mat4 World::getProjectionViewModel()
{
	return m_projectionMatrix * m_camera.getViewMatrix() * m_quad.getTransform();
}
