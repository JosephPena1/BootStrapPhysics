#pragma once
#include "Shader.h"
#include "World.h"

struct GLFWwindow;

class Application
{
public:
	Application();
	Application(int width, int height, const char* title);
	~Application();

	int run();

private:
	int start();
	int update(double deltaTime);
	int draw(aie::ShaderProgram* shader);
	int end();

	bool getGameOver();

private:
	GLFWwindow* m_window = nullptr;
	int m_width, m_height;
	const char* m_title;

	aie::ShaderProgram* m_shader = nullptr;

	World* m_world;
};
