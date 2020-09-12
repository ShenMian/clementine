// Copyright 2020 SMS
// License(Apache-2.0)
// 球

#include <time.h>
#include <clem/clem.hpp>

#ifdef OS_WIN
#include <windows.h>
#define sleep(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep(ms) usleep(ms * 1000)
#endif

using namespace std;

const int num = 5;

int main()
{
	// Terminal::Cursor::hide();
	srand(time(nullptr));

	Scene          scene(Terminal::getWindowSize());
	SimplePhysics  physics;
	CommonRenderer renderer(Terminal::getWindowSize());

	scene.setPhysics(&physics);
	scene.setRenderer(&renderer);
	physics.addBorder(Rect(0, 25, 30, 15));

	Texture         texture(Size(1, 1), {'O', Attribute(fore::yellow)});
	vector<Entity*> balls;

	for(int i = 0; i < num; i++)
	{
		auto ball = new Entity(texture);
		ball->setPosition({0, 0});
		balls.push_back(ball);
	}

	while(true)
	{
		scene.update();
		sleep(50);
	}
}
