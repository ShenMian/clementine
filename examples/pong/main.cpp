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
	auto director = Director::getInstance();
	auto size     = director->getWinSize();

	Scene  scene;
	Factor factor(size);
	scene.addFactor(&factor);

	auto& texture = factor.getTexture();
	texture.drawCycle(Point(size.x / 2, size.y / 2), 10, Tile('*', Fore::green));
	texture.drawCycle(Point(size.x / 2, size.y / 2), 5, Tile('*', Fore::yellow));
	texture.drawCycle(Point(size.x / 2, size.y / 2), 2, Tile('*', Fore::red));
	
	director->pushScene(&scene);
	director->run();
}
