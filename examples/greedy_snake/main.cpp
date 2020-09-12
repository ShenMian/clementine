// Copyright 2020 SMS
// License(Apache-2.0)
// 贪吃蛇

#include <clem/clem.hpp>
#include "snake.hpp"
#include <time.h>

#ifdef OS_WIN
#include <windows.h>
#define sleep(ms) Sleep(ms)
#else
#include <unistd.h>
#define sleep(ms) usleep(ms * 1000)
#endif

using Attr = Attribute;

const float snack_speed = 0.2;

int main()
{
	srand(time(nullptr));                                // 初始化随机数发生器
	Terminal::Cursor::hide();                            // 隐藏光标
	auto          winSize = Terminal::getWindowSize();   // 获取终端窗口大小
	Scene         scene;                                 // 创建场景
	BasicPhysics  physics;                               // 创建物理引擎组件
	Snake         snake(scene);                          // 将蛇加入场景
	physics.setVelocity({0, snack_speed});               // 设置蛇的初速度
	snake.addComponent(&physics);                        // 为蛇添加物理引擎
	snake.setPosition(Vector(winSize.x, winSize.y) / 2); // 设置蛇的位置到场景中央

	enum
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};
	KeyboardInput keyboard; // 创建键盘输入
	keyboard.bind('W', UP);
	keyboard.bind('S', DOWN);
	keyboard.bind('A', LEFT);
	keyboard.bind('D', RIGHT);

	while(true)
	{
		for(auto event : keyboard.update())
			switch(event)
			{
			case UP:
				physics.setVelocity({0, snack_speed});
				break;

			case DOWN:
				physics.setVelocity({0, -snack_speed});
				break;

			case LEFT:
				physics.setVelocity({-snack_speed, 0});
				break;

			case RIGHT:
				physics.setVelocity({snack_speed, 0});
				break;
			}

		scene.update();
		scene.render();

		sleep(50);
	}

	(void)getchar();
	return 0;
}
