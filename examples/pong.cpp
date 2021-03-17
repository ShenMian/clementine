// Copyright 2021 SMS
// License(Apache-2.0)

#include "clem.h"
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <assert.h>

using namespace std;

class Pong : public Application
{
public:
	Pong()
			: Application("Pong")
	{
		scene = make_shared<Scene>();
		pushScene(scene);

		auto ball = scene->createEntity();

		Sprite sprite;
		sprite.setSize({1, 1});
		sprite.drawPoint({0, 0}, Tile('O'));

		ball.addComponent<Sprite>(sprite);
	}

private:
	shared_ptr<Scene> scene;
};

Application* CreateApplication()
{
	return new Pong();
}





/*
int func()
{
	Cursor::setVisible(false);
	auto  director = Director::getInstance();
	Scene scene;

	Size winSize(width, height);
	frameBuffer.setSize(winSize);

	Bar bar(scene);
	bar.setPosition({1, winSize.y / 2.0f - 2});

	Ball ball(scene);
	ball.setPosition({winSize.x / 2.0f, winSize.y / 2.0f});
	ball.setVelocity({-30, 0});

	Ball testA(scene);
	testA.setPosition({117, 14});
	Ball testB(scene);
	testB.setPosition({2, 14});

	director->setMsPerRender(1000 / 60);
	director->pushScene(scene);
	director->run();
	while(true)
		;
	return 0;
}
*/
