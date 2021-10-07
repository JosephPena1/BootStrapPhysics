#include "Time.h"
#include "GLFW/glfw3.h"

double Time::getDeltaTime()
{
	//Declare instance of static Time class to use private variables
	static Time time;

	//Calculate deltaTime
	time.m_currentTime = glfwGetTime();
	time.m_deltaTime = time.m_currentTime - time.m_previousTime;
	if (time.m_deltaTime > 0.1)
		time.m_deltaTime = 0.1;
	time.m_previousTime = time.m_currentTime;

	//Return deltaTime
	return time.m_deltaTime;
}
