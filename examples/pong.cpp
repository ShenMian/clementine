// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"
#include <cassert>
#include <iostream>
#include <stdio.h>

using namespace std;

class Pong : public Application
{
public:
	Pong()
			: Application("Pong")
	{
		auto scene = make_shared<Scene>();
		pushScene(scene);

		auto ball = scene->createEntity();

		Sprite sprite;
		sprite.setSize({1, 1});
		sprite.drawPoint({0, 0}, Tile('O'));

		ball.addComponent<Sprite>(sprite);
	}

	~Pong()
	{
	}
};

Application* CreateApplication()
{
	return new Pong();
}
