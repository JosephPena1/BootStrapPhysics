#include "gl_core_4_4.h"
#include "GLFW/glfw3.h"
#include <iostream>

void end(GLFWwindow* window)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}

int main()
{
	//Initialize
	if (glfwInit() == GLFW_FALSE)
		return -1;

	//Creates a window
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Graphics", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return-2;
	}
	glfwMakeContextCurrent(window);

	//Load OpenGL
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		end(window);
		return -3;
	}
	int majorVersion = ogl_GetMajorVersion();
	int minorVersion = ogl_GetMinorVersion();
	printf("OpenGL Version: %i.%i\n", majorVersion, minorVersion);

	//Cleanup and exit
	end(window);
	return 0;
}
