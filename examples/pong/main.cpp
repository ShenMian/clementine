// Copyright 2020 SMS
// License(Apache-2.0)
// 乒乓球

#include <clem/clem.hpp>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <assert.h>

using namespace std;

int main()
{
#ifdef OS_WIN
	// 开启 VT100模式
	DWORD mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) // 开启 VT100模式
		assert(false);
#endif

	auto director = Director::getInstance();
	auto size     = director->getWinSize();

	Texture texture(size);
	Color   green(Fore::green);

	texture.drawCycle(Point(size.x / 2, size.y / 2), 10, Tile('*', green));
	
	Factor factor(texture);
	
	Scene scene;
	scene.addFactor(&factor);

	director->pushScene(&scene);
	director->run();
}
