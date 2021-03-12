﻿// Copyright 2020 SMS
// License(Apache-2.0)
// Table tennis

#include "clem/clem.hpp"
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
#include <random>

#include "player.hpp"

int main()
{
	Cursor::setVisible(false);
	auto director = Director::getInstance();
	Scene scene;
	

	Player playerA(scene);
	playerA.bind(Keyboard::Key::W, Keyboard::Key::S);
	playerA.setPosition({1, 12});
	
	Player playerB(scene);
	playerB.bind(Keyboard::Key::up, Keyboard::Key::down);
	playerB.setPosition({118, 12});

	director->pushScene(scene);
	director->run();
	while(true)
		;
}
