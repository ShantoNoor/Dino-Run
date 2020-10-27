#include "Engine.h"

Engine* game = nullptr;
std::string gameName = "Dino Run";

int main(int argc, char* argv[])
{
	game = new Engine();

	game->init(gameName.c_str());

    game->load();

	while(game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

    game->close();

	return 0;
}