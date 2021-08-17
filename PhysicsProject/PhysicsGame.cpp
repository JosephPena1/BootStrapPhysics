#include "PhysicsGame.h"
#include "Input.h"
#include "Font.h"
#include "Gizmos.h"
#include "glm/ext.hpp"

bool PhysicsGame::startup()
{
	m_renderer = new aie::Renderer2D();
	setBackgroundColour(0.2f, 0.1f, 0.0f, 1.0f);

	m_font = new aie::Font("../bin/font/consolas.tts");

	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_font;
}

void PhysicsGame::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();


}

void PhysicsGame::draw()
{

}
