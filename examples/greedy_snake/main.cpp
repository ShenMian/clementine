// Copyright 2020 SMS
// License(Apache-2.0)

#include <clem/clem.hpp>
#include "snake.hpp"

const float snack_speed = 0.2;

int main()
{
	auto director = Director::instance();
	Scene scene;
	Snake snake;
	
	scene.addFactor(&snake);
	
	director->pushScene(&scene);
	director->run();

	getchar();
	return 0;
}
