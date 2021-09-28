#include "Application.h"
#include "GLFW/glfw3.h"

Application::Application()
{

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

	while (getGameOver())
	{
		update();
	}

	exitCode = end();
	if (exitCode)
		return exitCode;

	return 0;
}

int Application::start()
{
	return -1;
}

int Application::update()
{
	return 0;
}

int Application::end()
{
	return 0;
}

bool Application::getGameOver()
{
	bool gameIsOver = glfwWindowShouldClose(m_window);
	gameIsOver = gameIsOver || glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

	return gameIsOver;
}
