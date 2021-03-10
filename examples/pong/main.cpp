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
#include <clem/frame_buffer.h>

int main()
{
	Cursor::setVisible(false);
	auto director = Director::getInstance();
	auto winSize  = director->getWinSize();

	FrameBuffer buffer(winSize);
	buffer.drawRectFill(Rect(Point(0, 0), Size(120, 30)), Tile('.'));
	buffer.swapBuffer();
	buffer.render();

	Scene scene;

	Factor player(Tile('@', Fore::green));
	Keyboard keyboard;
	keyboard.bindOnChanged(Keyboard::Key::left, [&](bool state) {
		if(state)
			player.setVelocity({-4, 0});
		else
			player.setVelocity({0, 0});
	});
	keyboard.bindOnChanged(Keyboard::Key::right, [&](bool state) {
		if(state)
			player.setVelocity({4, 0});
		else
			player.setVelocity({0, 0});
	});
	player.addComponent(keyboard);
	player.setPosition({10, 5});
	
	scene.addFactor(player);

	director->pushScene(scene);
	director->run();

	while(true)
		;
}
