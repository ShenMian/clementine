// Copyright 2020 SMS
// License(Apache-2.0)
// 乒乓球

#include <clem/clem.hpp>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <assert.h>

using namespace std;

#include <clem/input/keyboard.h>

int main()
{
	Cursor::setVisible(false);
	auto director = Director::getInstance();
	auto size     = director->getWinSize();

	// Factor factor(size);
	// Factor player(Tile('@', Fore::green));
	Factor player;

	Keyboard keyboard;
	keyboard.bind(Keyboard::Key::esc, [&player](bool state) {
		printf("KEY STATE CHANGED\n");
		player.setPosition(player.getPosition() + Point(0, 1));
	});

	player.addComponent(keyboard);

	Scene scene;
	scene.addFactor(&player);

	director->pushScene(scene);
	director->run();
}
