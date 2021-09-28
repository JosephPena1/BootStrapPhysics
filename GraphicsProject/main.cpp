#include "Application.h"

int main()
{
	int exitCode = 0;

	Application* game = new Application(1280,720,"Graphics");

	exitCode = game->run();

	delete game;

	return exitCode;
}
