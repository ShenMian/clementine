﻿// Copyright 2021 SMS
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
		scene = make_shared<Scene>(); // 创建场景 scene, 用于管理实体
		pushScene(scene);             // 将 scene 压入堆栈

		constexpr auto ball_speed = 0.6f;

		// 1. 创建乒乓球 Sprite
		Sprite ballSprite({1, 1});
		ballSprite.drawPoint({0, 0}, Tile('O', Color::yellow));

		// 1. 创建乒乓球
		auto ball = scene->createEntity("ball");                      // 向 scene 申请创建一个实体 ball
		ball.addComponent<Sprite>(ballSprite);                        // 为 ball 创建一个大小为 1,1 的 Sprite组件. 并在 0,0 处绘制一个 Tile
		ball.addComponent<Rigidbody>().velocity = {ball_speed, 0.02f}; // 为 ball 创建一个 Rigidbody 组件, 并设置初速度
		ball.getComponent<Transform>().position = {39, 12};           // 设置 ball 的位置, Transform 组件默认存在

		// 3. 创建乒乓球球拍 Sprite
		Sprite batSprite({1, 5});
		batSprite.fillRect(Rect({0, 0}, {1, 5}), Tile('#', Color::blue));

		// 4. 创建两个乒乓球拍
		auto bat1 = scene->createEntity("bat1");
		auto bat2 = scene->createEntity("bat2");
		bat1.addComponent<Sprite>(batSprite); // 添加一个复制 batSprite 的 Sprite 组件
		bat2.addComponent<Sprite>(batSprite);
		bat1.addComponent<Rigidbody>();
		bat2.addComponent<Rigidbody>();
		bat1.getComponent<Transform>().position = {1, 10};
		bat2.getComponent<Transform>().position = {78, 10};

		// 5. Bat1 由玩家控制
		EventDispatcher::getInstance().addListener(Event::Type::key, [&](Event* e) {
			auto  event = dynamic_cast<KeyEvent*>(e);
			auto& body  = scene->getEntityByTag("bat1").getComponent<Rigidbody>();
			if(event->state == false)
				body.velocity = {0, 0};
			else if(event->keyCode == KeyCode::W)
				body.velocity = {0, -0.3f};
			else if(event->keyCode == KeyCode::S)
				body.velocity = {0, 0.3f};
		});

		// 6. Bat2 由AI控制, 不推测路径
		bat2.addComponent<Script>().onUpdate = [&](float dt) {
			auto& bat        = scene->getEntityByTag("bat2");
			auto  ballPos    = scene->getEntityByTag("ball").getComponent<Transform>().position;
			auto& batBody    = bat.getComponent<Rigidbody>();
			auto  batPos     = bat.getComponent<Transform>().position;
			auto& batSize    = bat.getComponent<Sprite>().getSize();
			auto  batCenter  = batPos.y + (int)batSize.y / 2;
			batBody.velocity = Vec2(0, ballPos.y - batCenter).normalize() * 0.3f;
		};

		ball.addComponent<Script>().onUpdate = [&](float dt) {
			auto& ball   = scene->getEntityByTag("ball");
			auto& pos    = ball.getComponent<Transform>().position;
			auto& vel    = ball.getComponent<Rigidbody>().velocity;
			auto& sprite = ball.getComponent<Sprite>();
			if(pos.x < 0 || pos.x >= 80)
			{
				vel.x = -vel.x;
				vel.y += (float)random.getInt32(-5, 5) / 100;
				vel = vel.normalize() * 0.6f;
			}
			else if(pos.y < 0 || pos.y >= 25)
			{
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-5, 5) / 100;
				vel = vel.normalize() * 0.6f;
			}
		};
	}

private:
	std::shared_ptr<Scene> scene;
	Random                 random;
};

#include "chess.cpp"

Application* CreateApplication()
{
	return new Pong;
}
