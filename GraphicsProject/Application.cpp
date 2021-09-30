#include "Application.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include <iostream>

Application::Application() : Application(1280, 720, "Window")
{

}

Application::Application(int width, int height, const char* title)
{
	m_width = width;
	m_height = height;
	m_title = title;
}

Application::~Application()
{

}

int Application::run()
{
	int exitCode = 0;

	exitCode = start();
	if (exitCode)
		return exitCode;

	while (!getGameOver())
	{
		//Update and draw
		exitCode = update();
		if (exitCode)
			return exitCode;

		exitCode = draw();
		if (exitCode)
			return exitCode;
	}

	exitCode = end();
	if (exitCode)
		return exitCode;

	return 0;
}

int Application::start()
{
	//Initialize
	if (glfwInit() == GLFW_FALSE)
		return -1;

	//Creates a window
	m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);
	if (!m_window)
	{
		glfwTerminate();
		return -2;
	}
	glfwMakeContextCurrent(m_window);

	//Load OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
		return -3;
	}
	//Prints out the OpenGL version to the console
	int majorVersion = ogl_GetMajorVersion();
	int minorVersion = ogl_GetMinorVersion();
	printf("OpenGL Version: %i.%i\n", majorVersion, minorVersion);

	//Initializes the screen
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//Initialize the shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "simpleVert.shader");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "simpleFrag.shader");

	if (!m_shader.link())
	{
		printf("Shader Error: %s\n", m_shader.getLastError());
		return -10;
	}

	//Initialize the quad
	m_quad.start();

	//Create camera transforms
	m_viewMatrix = glm::lookAt(
		glm::vec3(10, 10, 10),
		glm::vec3(0),
		glm::vec3(0, 1, 0)
	);

	m_projectionMatrix = glm::perspective(
		glm::pi<float>() / 4.0f,
		(float)m_width / (float)m_height,
		0.001f,
		1000.0f
	);

	return 0;
}

int Application::update()
{
	if (!m_window)
		return -4;

	glfwPollEvents();

	return 0;
}

int Application::draw()
{
	if (!m_window)
		return -5;

	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_shader.bind();

	glm::mat4 projectViewModel = m_projectionMatrix * m_viewMatrix * m_quad.getTransform();
	m_shader.bindUniform("projectionViewModel", projectViewModel);

	m_quad.draw();

	glfwSwapBuffers(m_window);

	return 0;
}

int Application::end()
{
	if (!m_window)
		return -6;

	glfwDestroyWindow(m_window);
	glfwTerminate();

	return 0;
}

bool Application::getGameOver()
{
	if (!m_window) 
		return true;

	bool gameIsOver = glfwWindowShouldClose(m_window);
	gameIsOver = gameIsOver || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	return gameIsOver;
}
