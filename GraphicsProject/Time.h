#pragma once

class Time
{
public:
	static double getDeltaTime();
	//maybe have an update, then just return deltatime in a getter.

private:
	double m_currentTime = 0.0;
	double m_previousTime = 0.0;
	double m_deltaTime = 0.0;
};
