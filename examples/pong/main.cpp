// Copyright 2020 SMS
// License(Apache-2.0)
// 球

#include <time.h>
#include <clem/clem.hpp>
#include <iostream>

#ifdef OS_WIN
#include <windows.h>
#define sleep(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep(ms) usleep(ms * 1000)
#endif

using namespace std;

int main()
{
	Color normal(mode_normal);
	Color green(fore_green);
	cout << green() << "Green" << normal() << endl;
	getchar(); getchar();

	Terminal::Cursor::hide();
	srand(time(nullptr));

	Scene          scene(Terminal::getWindowSize());
	SimplePhysics  physics;
	CommonRenderer renderer(Terminal::getWindowSize());

	scene.setPhysics(&physics);
	scene.setRenderer(&renderer);
	physics.addBorder(Rect(0, 25, 30, 15));

	Texture         texture(Size(1, 1), {'O', Attribute(fore::yellow)});
	vector<Entity*> balls;

	while(true)
	{
		scene.update();
		sleep(50);
	}
}
