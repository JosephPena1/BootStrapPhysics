#pragma once
#include"Application.h"
#include "Renderer2D.h"
#include "PhysicsScene.h"

class Sphere;

class PhysicsGame : public aie::Application
{
public:
	PhysicsGame() {}
	~PhysicsGame() {}

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

private:
	bool m_setTimer;
	float m_time;
	aie::Renderer2D* m_renderer;
	aie::Font* m_font;
	Sphere* m_cue;

	PhysicsScene* m_scene;
};

