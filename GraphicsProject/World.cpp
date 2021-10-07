#include "World.h"
#include "glm/ext.hpp"
#include "GLFW/glfw3.h"

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

void World::update(double deltaTime)
{
	int keyForward = GLFW_KEY_W;
	int keyBackward = GLFW_KEY_S;
	int keyLeft = GLFW_KEY_A;
	int keyRight = GLFW_KEY_D;
	int keyUp = GLFW_KEY_E;
	int keyDown = GLFW_KEY_Q;

	float cameraSpeed = 1.0f;
	double cameraSensitivity = 0.5f;

	//Calculate the cameras forward vector
	glm::vec3 cameraForward = glm::vec3(0.0f, 0.0f, 1.0f);
	//Calculate the camera right vector
	glm::vec3 cameraRight = glm::vec3(1.0f, 0.0f, 0.0f);
	//Calaculate the camera up vector
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	//Get current mouse coordinates
	glfwGetCursorPos(m_window, &m_currentMouseX, &m_currentMouseY);

	//Rotate camera using change in mouse position
	double deltaMouseX = m_currentMouseX - m_previousMouseX;
	double deltaMouseY = m_currentMouseY - m_previousMouseY;

	if (deltaMouseX != 0.0 && deltaMouseY != 0.0)
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::rotate(cameraTransform, (float)(deltaMouseX * cameraSensitivity * deltaTime), cameraUp);
		cameraTransform = glm::rotate(cameraTransform, (float)(deltaMouseY * cameraSensitivity * deltaTime), cameraRight);
		m_camera.setTransform(cameraTransform);
	}

	//Store previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;
	
	//Get forward input
	if (glfwGetKey(m_window, keyForward))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get backward input
	if (glfwGetKey(m_window, keyBackward))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, -cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get right input
	if (glfwGetKey(m_window, keyRight))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, -cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get left input
	if (glfwGetKey(m_window, keyLeft))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get up input
	if (glfwGetKey(m_window, keyUp))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, -cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get down input
	if (glfwGetKey(m_window, keyDown))
	{
		glm::mat4 cameraTransform = m_camera.getTransform();
		cameraTransform = glm::translate(cameraTransform, cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

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
