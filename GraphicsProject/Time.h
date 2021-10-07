#pragma once

class Time
{
public:
	static double getDeltaTime();

private:
	double m_currentTime = 0.0;
	double m_previousTime = 0.0;
	double m_deltaTime = 0.0;
};
