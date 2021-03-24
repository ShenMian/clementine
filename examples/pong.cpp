// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"
#include <cassert>
#include <cfloat>
#include <iostream>
#include <stdio.h>

using namespace std;

constexpr float ball_speed           = 0.8f;  // 球的移动速度, 始终恒定
constexpr float player_speed         = 0.15f; // 玩家乒乓球拍的移动速度
constexpr float ai_speed             = 0.1f;  // AI 乒乓球拍的移动速度
constexpr float random_rebound_angle = 5.0f;  // 碰撞时随机调整角度系数

int player_score = 0;
int ai_score     = 0;

class Pong : public Application
{
public:
	Pong()
			: Application("Pong"), scene(make_shared<Scene>())
	{
		pushScene(scene);             // 将 scene 压入堆栈

		// 1. 创建乒乓球 Sprite
		Sprite ballSprite({1, 1});
		ballSprite.drawPoint({0, 0}, Tile('O', Color::yellow));

		// 1. 创建乒乓球
		auto ball = scene->createEntityWithTag("ball");                       // 向 scene 申请创建一个实体 ball
		ball.addComponent<Sprite>(ballSprite);                         // 为 ball 创建一个复制 ballSprite 的 Sprite 组件
		ball.addComponent<Rigidbody>().velocity = {ball_speed, 0.05f}; // 为 ball 创建一个 Rigidbody 组件, 并设置初速度
		ball.getComponent<Transform>().position = {39, 12};            // 设置 ball 的位置, Transform 组件默认存在

		// 3. 创建乒乓球球拍 Sprite
		Sprite batSprite({1, 5});
		batSprite.fillRect(Rect2i({0, 0}, {1, 5}), Tile('#', Color::blue));

		// 4. 创建两个乒乓球拍
		auto bat1 = scene->createEntityWithTag("bat1");
		auto bat2 = scene->createEntityWithTag("bat2");
		bat1.addComponent<Sprite>(batSprite);
		bat2.addComponent<Sprite>(batSprite);
		bat1.addComponent<Rigidbody>();
		bat2.addComponent<Rigidbody>();
		bat1.getComponent<Transform>().position = {2, 10};
		bat2.getComponent<Transform>().position = {77, 10};

		// 5. Bat1 由玩家控制
		// 为 bat1 创建一个事件监听器, 监听按键事件
		EventDispatcher::getInstance().addListener(Event::Type::key, [&](Event* e) {
			auto  event = dynamic_cast<KeyEvent*>(e);
			auto& body  = scene->getEntityByTag("bat1").getComponent<Rigidbody>(); // 通过 Tag 组件获取 bat1 实体的 Rigidbody 组件
			if(event->state == false)
				body.velocity = {0, 0};
			else if(event->keyCode == KeyCode::W)
				body.velocity = {0, -player_speed};
			else if(event->keyCode == KeyCode::S)
				body.velocity = {0, player_speed};
		});

		// 6. Bat2 由AI控制, 不推测路径
		// 为 bat2 创建一个脚本
		bat2.addComponent<Script>().onUpdate = [&](float dt) {
			auto  bat     = scene->getEntityByTag("bat2");
			auto  ballPos = scene->getEntityByTag("ball").getComponent<Transform>().position;
			auto& batBody = bat.getComponent<Rigidbody>();
			auto  batPos  = bat.getComponent<Transform>().position;
			auto& batSize = bat.getComponent<Sprite>().getSize();

			// 获取 bat2 的 Sprite 的几何中心
			auto batCenter = batPos + batSize / 2;

			// 以 ai_speed 速度向 ball 所在的 y 坐标移动
			batBody.velocity = Vector2f(0, ballPos.y - batCenter.y).normalize() * ai_speed;
		};

		// TODO: 碰撞时被回调, 调整随机角度
		ball.addComponent<Script>().onUpdate = [&](float dt) {
			auto  ball   = scene->getEntityByTag("ball");
			auto& pos    = ball.getComponent<Transform>().position;
			auto& vel    = ball.getComponent<Rigidbody>().velocity;
			auto& sprite = ball.getComponent<Sprite>();
			if(pos.x < 1 || pos.x >= 79)
			{
				if(pos.x < 1)
					ai_score++;
				else
					player_score++;

				vel.x = -vel.x;
				vel.y += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
			}
			else if(pos.y < 1 || pos.y >= 24)
			{
				vel.y = -vel.y;
				vel.x += (float)random.getInt32(-random_rebound_angle, random_rebound_angle) / 100;
			}
			else
				return;
			vel = vel.normalize() * ball_speed;
		};

		// 7. 创建场景中的其他元素
		auto  board       = scene->createEntityWithTag("board");
		auto& boardSprite = board.addComponent<Sprite>(Size2(80, 25));
		boardSprite.drawRect(Rect2i({0, 0}, {79, 24}), Tile('#'));
		boardSprite.fillRect(Rect2i({39, 1}, {2, 23}), Tile('.', Color::green));
		board.addComponent<Script>().onUpdate = [&](float dt) {
			boardSprite.drawString({34, 2}, to_wstring(player_score));
			boardSprite.drawString({44, 2}, to_wstring(ai_score));
		};
	}

private:
	Random                 random;
	shared_ptr<Scene> scene;
};

/*
Application* CreateApplication()
{
	return new Pong;
}
*/

