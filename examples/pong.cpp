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
		scene = make_shared<Scene>();  // 创建场景 scene, 用于管理实体
		pushScene(scene);              // 将 scene 压入堆栈

		// 1. 创建乒乓球
		auto  ball   = scene->createEntity("ball");         // 向 scene 申请创建一个实体 ball
		auto& sprite = ball.addComponent<Sprite>();         // 为 ball 创建一个 Sprite 组件
		auto& body   = ball.addComponent<Rigidbody>();      // 为 ball 创建一个 Rigidbody 组件
		sprite.setSize({1, 1});                             // 设置 Sprite 的大小, 即可绘制区域的大小
		sprite.drawPoint({0, 0}, Tile('O'));                // 在 0,0 处绘制一个 Tile
		ball.getComponent<Transform>().position = {40, 12}; // 设置 ball 的位置, Transform 组件默认存在
		body.velocity                           = {0.1, 0}; // 设置初速度

		// 2. 创建乒乓球球拍的 Sprite, 作为两个乒乓球拍 Sprite 组件的模板
		Sprite batSprite;
		batSprite.setSize({1, 5});
		batSprite.fillRect(Rect({0, 0}, {1, 5}), Tile('#'));

		// 3. 创建两个乒乓球拍
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

Application* CreateApplication()
{
	return new Pong();
}
