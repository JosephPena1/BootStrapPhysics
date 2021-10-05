#pragma once
#include "Shader.h"
#include "Camera.h"
#include "Quad.h"
#include "Light.h"
#include "glm/mat4x4.hpp"

class World
{
public:
	World(int width, int height);
	~World() {}

	void start();
	void update(float deltaTime);
	void draw(aie::ShaderProgram* shader);
	void end();

	glm::mat4 getProjectionView();

private:
	int m_width = 1280, m_height = 720;
	Camera m_camera = Camera();
	glm::mat4 m_projectionMatrix = glm::mat4(1);
	
	Quad m_quad;
	Light m_light;
};
