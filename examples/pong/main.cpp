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
	Cursor::setVisible(false);
	auto director = Director::getInstance();
	auto size     = director->getWinSize();

	Scene  scene;
	Factor factor(size);
	scene.addFactor(&factor);

	auto& texture = factor.getTexture();
	auto r = min(size.x, size.y) / 2 - 1;
	texture.drawCycle(Point(size.x / 2, size.y / 2), r, Tile('*', Fore::green));
	texture.drawCycle(Point(size.x / 2, size.y / 2), r - 1, Tile('*', Fore::yellow));
	texture.drawCycle(Point(size.x / 2, size.y / 2), r - 2, Tile('*', Fore::red));
	
	Logger::add(0, "test.log");
	Logger::write(0, Level::info, "It's a simple test.");

	director->pushScene(&scene);
	director->run();
}
