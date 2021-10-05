#include "Application.h"

int main()
{
	Application* game = new Application(1280,720,"Graphics");

	int exitCode = game->run();

	delete game;

	return exitCode;
}
