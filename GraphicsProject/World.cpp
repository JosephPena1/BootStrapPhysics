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
	m_quad.setTransform(glm::mat4(10.0f));
	m_quad.setColor(glm::vec4(0.6f, 0.0f, 0.6f, 1.0f));
	m_quad.start();
	//Initialize the light
	m_light.setDirection(glm::vec3(-1.0f));
	m_light.setAmbient(glm::vec4(0.6f, 0.6f, 0.0f, 1.0f));
	m_light.setDiffuse(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_light.setSpecular(glm::vec4(1,1,1,1));

	//Create camera transforms
	m_camera.setTransform(glm::lookAt(
		glm::vec3(2, 2, 2),
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
	shader->bindUniform("cameraPosition", glm::vec4(1));
	shader->bindUniform("lightDirection", m_light.getDirection());
	shader->bindUniform("lightAmbient", m_light.getAmbient());
	shader->bindUniform("lightDiffuse", m_light.getDiffuse());
	shader->bindUniform("lightSpecular", m_light.getSpecular());
	shader->bindUniform("specularPower", m_light.getSpecularPower());
	
	m_quad.draw(shader);
}

void World::end()
{

}

glm::mat4 World::getProjectionView()
{
	return m_projectionMatrix * m_camera.getTransform();
}
