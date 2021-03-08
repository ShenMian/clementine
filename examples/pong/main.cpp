// Copyright 2020 SMS
// License(Apache-2.0)
// 乒乓球

#include <clem/clem.hpp>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <assert.h>
#include <chrono>
#include <thread>

using std::chrono::seconds;
using std::this_thread::sleep_for;

using namespace std;

#include <clem/input/keyboard.h>

int main()
{
	Cursor::setVisible(false);
	auto director = Director::getInstance();

	Scene scene;

	Factor player(Tile('@', Fore::green));
	Keyboard keyboard;
	keyboard.bindOnPressed(Keyboard::Key::left, [&]() {
		player.setPosition(player.getPosition() + Point(-1, 0));
		// player.setVelocity({-1, 0});
	});
	keyboard.bindOnPressed(Keyboard::Key::right, [&]() {
		player.setPosition(player.getPosition() + Point(1, 0));
		// player.setVelocity({1, 0});
	});
	player.addComponent(keyboard);
	player.setPosition({10, 5});
	
	scene.addFactor(player);

	director->pushScene(scene);
	director->run();

	while(true)
		;
}
