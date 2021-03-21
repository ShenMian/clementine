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
		/*auto& dispatcher = EventDispatcher::getInstance();
		dispatcher.addListener(Event::Type::mouse, [](Event* e) {
			auto event = dynamic_cast<MouseEvent*>(e);
			auto& pos   = event->getPosition();
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {(short)pos.x, (short)pos.y});
			printf("*");
		});*/

		scene = make_shared<Scene>();  // 创建场景 scene, 用于管理实体
		pushScene(scene);              // 将 scene 压入堆栈

		// 1. 创建乒乓球 Sprite
		Sprite ballSprite({1 ,1});
		ballSprite.drawPoint({0, 0}, Tile('O', Color::yellow));

		// 1. 创建乒乓球
		auto ball = scene->createEntity("ball");            // 向 scene 申请创建一个实体 ball
		ball.addComponent<Sprite>(ballSprite);              // 为 ball 创建一个大小为 1,1 的 Sprite组件. 并在 0,0 处绘制一个 Tile
		ball.addComponent<Rigidbody>().velocity = {0.1, 0}; // 为 ball 创建一个 Rigidbody 组件, 并设置初速度
		ball.getComponent<Transform>().position = {40, 12}; // 设置 ball 的位置, Transform 组件默认存在

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
	}

private:
	std::shared_ptr<Scene> scene;
};

#include "chess.cpp"

Application* CreateApplication()
{
	return new Pong;
}
