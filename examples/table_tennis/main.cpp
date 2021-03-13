// Copyright 2021 SMS
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

class Ball : public Factor
{
public:
	explicit Ball(Scene& s)
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

class Bar : public Factor
{
public:
	Bar(Scene& s)
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

int main()
{
	Cursor::setVisible(false);
	auto director = Director::getInstance();
	Scene scene;
	
	/*
	Player playerA(scene);
	playerA.bind(Keyboard::Key::W, Keyboard::Key::S);
	playerA.setPosition({1, 12});
	
	Player playerB(scene);
	playerB.bind(Keyboard::Key::up, Keyboard::Key::down);
	playerB.setPosition({118, 12});
	*/

	Bar bar(scene);
	bar.setPosition({1, 12});

	Ball ball(scene);
	ball.setPosition({59, 14});
	ball.setVelocity({-30, 0});

	/*
	Ball testA(scene);
	testA.setPosition({117, 14});
	Ball testB(scene);
	testB.setPosition({2, 14});
	*/

	director->setMsPerRender(1000 / 60);
	director->pushScene(scene);
	director->run();
	while(true)
		;
}
