// Copyright 2020 SMS
// License(Apache-2.0)
// 乒乓球

#include <time.h>
#include <clem/clem.hpp>
#include <iostream>
#include <stdio.h>

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
	auto director = Director::instance();
	Size size = director->getWinSize();
	
	Texture texture(size);
	texture.drawCycle(Point(size.x / 2, size.y / 2), 5, Tile('.', fore_green));
	
	Factor factor(texture);
	
	Scene scene;
	scene.getDefaultCamera()->setSize(size);
	scene.addFactor(&factor);

	director->pushScene(&scene);
	director->run();

	getchar();
	getchar();
}
