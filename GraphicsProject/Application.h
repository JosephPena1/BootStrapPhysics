#pragma once

class Application
{
public:

	Application();
	~Application();

	int run();

private:

	int start();
	int update();
	int end();

	bool getGameOver();

private:

	GLFWwindow* m_window;
};
