#include "Engine.h"

int main(int argc, char* argv[])
{
	Engine::get()->init("Dino Run");

    Engine::get()->load();

	while(Engine::get()->isRunning())
	{
		Engine::get()->handleEvents();
		Engine::get()->update();
		Engine::get()->render();
	}

    Engine::get()->close();

	return 0;
}