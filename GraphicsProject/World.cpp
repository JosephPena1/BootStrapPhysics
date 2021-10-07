#include "World.h"
#include "glm/ext.hpp"
//#include "GLFW/glfw3.h"

World::World(int width, int height)
{
	m_width = width;
	m_height = height;
}

void World::start()
{
	//Initialize the OBJ mesh
	m_objMesh.load("Bunny.obj", false);
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
	Transform cameraTransform = m_camera.getTransform();
	//cameraTransform.setPosition(glm::vec3(1.0f));
	//cameraTransform.setRotation(glm::vec3(45.0f, 45.0f, 0.0f));
	m_camera.setTransform(cameraTransform);
	/*m_camera.setTransform(glm::lookAt(
		glm::vec3(2, 2, 2),
		glm::vec3(0),
		glm::vec3(0, 1, 0))
	);*/

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

	float cameraSpeed = 3.0f;
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

	if (deltaMouseX != 0.0 || deltaMouseY != 0.0)
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.rotate(glm::vec3(deltaMouseY, deltaMouseX, 0) * (float)(cameraSensitivity * deltaTime));
		m_camera.setTransform(cameraTransform);
	}

	//Store previous mouse coordinates
	m_previousMouseX = m_currentMouseX;
	m_previousMouseY = m_currentMouseY;
	
	//Get forward input
	if (glfwGetKey(m_window, keyForward))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get backward input
	if (glfwGetKey(m_window, keyBackward))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraForward * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get right input
	if (glfwGetKey(m_window, keyRight))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get left input
	if (glfwGetKey(m_window, keyLeft))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraRight * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get up input
	if (glfwGetKey(m_window, keyUp))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(-cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

	//Get down input
	if (glfwGetKey(m_window, keyDown))
	{
		Transform cameraTransform = m_camera.getTransform();
		cameraTransform.translate(cameraUp * cameraSpeed * (float)deltaTime);
		m_camera.setTransform(cameraTransform);
	}

}

void World::draw(aie::ShaderProgram* shader)
{
	shader->bindUniform("cameraPosition", m_camera.getTransform().getPosition());
	shader->bindUniform("lightDirection", m_light.getDirection());
	shader->bindUniform("lightAmbient", m_light.getAmbient());
	shader->bindUniform("lightDiffuse", m_light.getDiffuse());
	shader->bindUniform("lightSpecular", m_light.getSpecular());
	shader->bindUniform("lightSpecularPower", m_light.getSpecularPower());
	m_quad.draw(shader);
	shader->bindUniform("modelMatrix", m_objTransform);
	m_objMesh.draw();
}

void World::end()
{

}

glm::mat4 World::getProjectionView()
{
	return m_projectionMatrix * m_camera.getTransform().getMatrix();
}
