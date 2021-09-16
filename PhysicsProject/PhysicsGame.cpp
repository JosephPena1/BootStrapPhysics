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
	setBackgroundColour(0.2f, 0.4f, 0.2f, 0.8f);

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_scene = new PhysicsScene();
	m_scene->setTimeStep(0.01f);
	m_scene->setGravity({0.0f, 0.0f});

	Sphere* cue = new Sphere(glm::vec2(-20, 0), glm::vec2(), 1, 5, glm::vec4(0.8f, 0.8f, 0.8f, 0.8f));
	m_scene->addActor(cue);
	m_cue = cue;

	Sphere* ball1 = new Sphere(glm::vec2(20, 0), glm::vec2(), 1, 5, glm::vec4(0.8f, 0.4f, 0.2f, 0.8f));
	m_scene->addActor(ball1);
	//ball1->applyForce(glm::vec2(200.0f, 0.0f));
	Sphere* ball2 = new Sphere(glm::vec2(30, 7), glm::vec2(), 1, 5, glm::vec4(0.4f, 0.4f, 0.8f, 0.8f));
	m_scene->addActor(ball2);
	//ball2->applyForce(glm::vec2(200.0f, 0.0f));
	Sphere* ball3 = new Sphere(glm::vec2(30, -7), glm::vec2(), 1, 5, glm::vec4(0.8f, 0.1f, 0.5f, 0.8f));
	m_scene->addActor(ball3);
	//ball3->applyForce(glm::vec2(200.0f, 0.0f));
	Sphere* ball4 = new Sphere(glm::vec2(40, 14), glm::vec2(), 1, 5, glm::vec4(0.5f, 0.6f, 0.0f, 0.5f));
	m_scene->addActor(ball4);
	//ball4->applyForce(glm::vec2(200.0f, 0.0f));
	Sphere* ball5 = new Sphere(glm::vec2(40, -14), glm::vec2(), 1, 5, glm::vec4(0.5f, 0.7f, 0.9f, 0.9f));
	m_scene->addActor(ball5);
	//ball5->applyForce(glm::vec2(200.0f, 0.0f));
	Sphere* ball6 = new Sphere(glm::vec2(40, 0), glm::vec2(), 1, 5, glm::vec4(0.2f, 0.4f, 0.8f, 0.9f));
	m_scene->addActor(ball6);
	//ball6->applyForce(glm::vec2(200.0f, 0.0f));

	//Boundary
	Plane* top = new Plane(glm::vec2(0.0f, -1.0f), -58.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(top);

	Plane* bottom = new Plane(glm::vec2(0.0f, 1.0f), -58.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(bottom);

	Plane* left = new Plane(glm::vec2(1.0f, 0.0f), -100.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
	m_scene->addActor(left);

	Plane* right = new Plane(glm::vec2(-1.0f, 0.0f), -100.0f, glm::vec4(0.2f, 0.8f, 0.2f, 0.8f));
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

	float speed = 2.0f;

	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_cue->applyForce({ speed, 0 });
	else if (input->isKeyDown(aie::INPUT_KEY_A))
		m_cue->applyForce({ -speed, 0 });
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_cue->applyForce({ 0, speed });
	else if (input->isKeyDown(aie::INPUT_KEY_S))
		m_cue->applyForce({ 0, -speed });

	m_scene->update(deltaTime);

	//Exit on Esc
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
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
