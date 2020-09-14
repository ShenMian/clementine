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

const float snack_speed = 0.2;

int main()
{
	srand(time(nullptr));                                // 初始化随机数发生器
	Terminal::Cursor::hide();                            // 隐藏光标
	auto          winSize = Terminal::getWindowSize();   // 获取终端窗口大小
	Scene         scene;                                 // 创建场景
	while(true)
	{
		scene.update();
		sleep(50);
	}

	(void)getchar();
	return 0;
}
