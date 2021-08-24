#include "PhysicsGame.h"
#include "Sphere.h"
#include "Plane.h"
#include "Input.h"
#include "Font.h"
#include "Gizmos.h"
#include "glm/ext.hpp"

bool PhysicsGame::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_renderer = new aie::Renderer2D();
	setBackgroundColour(0, 0, 0, 0);

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_scene = new PhysicsScene();
	m_scene->setTimeStep(0.01f);
	m_scene->setGravity({0.0f, 0.0f});


	Sphere* cue = new Sphere(glm::vec2(-20, 0), glm::vec2(), 5, 5, glm::vec4(0.8f, 0.2f, 0.2f, 0.8f));
	m_scene->addActor(cue);
	cue->applyForce(glm::vec2(100.0f, 0.0f));

	Sphere* ball1 = new Sphere(glm::vec2(20, 0), glm::vec2(), 1, 5, glm::vec4(0.2f, 0.2f, 0.2f, 0.8f));
	m_scene->addActor(ball1);
	Sphere* ball2 = new Sphere(glm::vec2(30, 7), glm::vec2(), 1, 5, glm::vec4(0.4f, 0.9f, 0.7f, 0.8f));
	m_scene->addActor(ball2);
	Sphere* ball3 = new Sphere(glm::vec2(30, -7), glm::vec2(), 1, 5, glm::vec4(0.6f, 0.0f, 0.5f, 0.8f));
	m_scene->addActor(ball3);
	Sphere* ball4 = new Sphere(glm::vec2(40, 14), glm::vec2(), 1, 5, glm::vec4(0.3f, 0.1f, 0.2f, 0.8f));
	m_scene->addActor(ball4);
	Sphere* ball5 = new Sphere(glm::vec2(40, -14), glm::vec2(), 1, 5, glm::vec4(0.2f, 0.5f, 0.2f, 0.8f));
	m_scene->addActor(ball5);
	Sphere* ball6 = new Sphere(glm::vec2(40, 0), glm::vec2(), 1, 5, glm::vec4(0.2f, 0.3f, 0.6f, 0.4f));
	m_scene->addActor(ball6);

	//Boundary
	Plane* top = new Plane(glm::vec2(0.0f, -1.0f), -55.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(top);

	Plane* bottom = new Plane(glm::vec2(0.0f, 1.0f), -55.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(bottom);

	Plane* left = new Plane(glm::vec2(1.0f, 0.0f), -95.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(left);

	Plane* right = new Plane(glm::vec2(-1.0f, 0.0f), -95.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(right);

	return true;
}

void PhysicsGame::shutdown()
{
	delete m_renderer;
	delete m_scene;
	delete m_font;

}

void PhysicsGame::update(float deltaTime)
{
	//Get the input instance
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_scene->update(deltaTime);

	//Exit on Esc
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	if (input->isKeyDown(aie::INPUT_KEY_UP))
		m_scene->setGravity({ m_scene->getGravity().x, m_scene->getGravity().y + 10});
	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		m_scene->setGravity({ m_scene->getGravity().x, m_scene->getGravity().y - 10 });
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_scene->setGravity({ m_scene->getGravity().x - 10, m_scene->getGravity().y});
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_scene->setGravity({ m_scene->getGravity().x + 10, m_scene->getGravity().y});
}

void PhysicsGame::draw()
{
	clearScreen();
	m_renderer->begin();

	//Draw the scene
	m_scene->draw();

	//Draw the gizmos
	static float aspectRatio = 16.0f / 9.0f;
	aie::Gizmos::draw2D(glm::ortho<float>(
		-100, 100,							   //Left & Right
		-100 / aspectRatio, 100 / aspectRatio, //Bottom & Top
		-1.0f, 1.0f));						   //zNear & zFar

	//Draw the fps
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_renderer->setRenderColour(1, 1, 1, 1);
	m_renderer->drawText(m_font, fps, 0.0f, 0.0f);
	m_renderer->end();
}
