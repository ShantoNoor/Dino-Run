#include "Engine.h"
#include "Timer.h"

int main(int argc, char* argv[])
{
	Engine::get()->init("Dino Run");

    Engine::get()->load();

	while(Engine::get()->isRunning())
	{
		Engine::get()->handleEvents();
		Engine::get()->update();
		Engine::get()->render();
		Timer::get()->tick();
	}

    Engine::get()->close();

	return 0;
}