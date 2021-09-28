#include "Application.h"
#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
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
	//Can also do [exitCode = start() != 0] but messes with exit codes
	if (exitCode)
		return exitCode;

	while (!getGameOver())
	{
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
