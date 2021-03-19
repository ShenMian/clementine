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
		// 创建场景 scene, 用于管理实体
		auto scene = make_shared<Scene>();

		// 将 scene 压入堆栈, 位于栈顶的场景将在游戏启动时被执行
		pushScene(scene);

		// 创建实体 ball, 通过向 scene 申请一个实体
		auto ball = scene->createEntity();

		// 为 ball 创建一个 Sprite 组件
		auto& sprite = ball.addComponent<Sprite>();

		// 设置 Sprite 的大小, 即可绘制区域的大小
		sprite.setSize({1, 1});

		// 在 0,0 处绘制一个 Tile
		sprite.drawPoint({0, 0}, Tile('O'));
	}

	~Pong()
	{
	}
};

Application* CreateApplication()
{
	return new Pong();
}
