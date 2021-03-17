// Copyright 2021 SMS
// License(Apache-2.0)

#include "clem.h"
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

class Pong : public Application
{
public:
	Pong()
			: Application("Pong")
	{
		scene = make_shared<NScene>();
		pushScene(scene);

		auto ball = scene->createEntity();

		NSprite sprite;
		sprite.setSize({1, 1});
		sprite.drawPoint({0, 0}, Tile('O'));

		ball.addComponent<NSprite>(sprite);

		puts(__FUNCTION__);
		puts("Press Ctrl+C to exit.");
	}

	~Pong()
	{
		puts(__FUNCTION__);
	}

private:
	shared_ptr<NScene> scene;
};

Application* CreateApplication()
{
	return new Pong();
}

class _Ball : public Factor
{
public:
	explicit _Ball(Scene& s)
			: Factor(s)
	{
		sprite.setSize({1, 1});
		sprite.drawPoint({0, 0}, Tile('O'));

		collider.setSize({1, 1});

		body.addCollider(collider);

		addComponent(sprite);
		addComponent(body);
	}

	void onCollision(Collider&, Collider&) override
	{
		body.velocity = -body.velocity;
	}

	void setVelocity(const Vec2& v)
	{
		body.velocity = v;
	}

private:
	Sprite      sprite;
	Rigidbody   body;
	BoxCollider collider;
};

class _Bar : public Factor
{
public:
	_Bar(Scene& s)
			: Factor(s)
	{
		sprite.setSize({1, 5});
		sprite.drawLine({0, 0}, {0, 4}, Tile('#'));

		collider.setSize({1, 5});

		body.addCollider(collider);

		addComponent(sprite);
		addComponent(body);
	}

private:
	Sprite      sprite;
	Rigidbody   body;
	BoxCollider collider;
};

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