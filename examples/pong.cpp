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
		createBall();
	}

	void createBall()
	{
		auto ball = scene->createEntity();           // 向 scene 申请创建一个实体 ball

		auto& sprite = ball.addComponent<Sprite>();  // 为 ball 创建一个 Sprite 组件
		sprite.setSize({1, 1});                      // 设置 Sprite 的大小, 即可绘制区域的大小
		sprite.drawPoint({0, 0}, Tile('O'));         // 在 0,0 处绘制一个 Tile

		auto& body = ball.addComponent<Rigidbody>(); // 为 ball 创建一个 Rigidbody 组件
	}

private:
	std::shared_ptr<Scene> scene;
};

Application* CreateApplication()
{
	return new Pong();
}
