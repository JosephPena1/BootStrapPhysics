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
	m_world = new World(width, height);
	m_width = width;
	m_height = height;
	m_title = title;

	m_shader = new aie::ShaderProgram();
}

Application::~Application()
{
	delete m_world;
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
		exitCode = update(glfwGetTime());
		if (exitCode)
			return exitCode;

		exitCode = draw(m_shader);
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
	m_shader->loadShader(aie::eShaderStage::VERTEX, "simpleVert.shader");
	m_shader->loadShader(aie::eShaderStage::FRAGMENT, "simpleFrag.shader");

	if (!m_shader->link())
	{
		printf("Shader Error: %s\n", m_shader->getLastError());
		return -10;
	}

	m_world->start();

	return 0;
}

int Application::update(float deltaTime)
{
	if (!m_window)
		return -4;

	m_world->update(deltaTime);

	glfwPollEvents();

	return 0;
}

int Application::draw(aie::ShaderProgram* shader)
{
	if (!m_window)
		return -5;

	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader->bind();

	shader->bindUniform("projectionViewMatrix", m_world->getProjectionView());

	m_world->draw(shader);

	glfwSwapBuffers(m_window);

	return 0;
}

int Application::end()
{
	if (!m_window)
		return -6;

	m_world->end();

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
