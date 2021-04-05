﻿// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;

class Game2048 : public Application
{
public:
	Game2048()
			: Application("2048")
	{
	}

	void init() override
	{
		pushScene(scene);

		auto& board = scene->createEntity("board");
		sprite = &board.addComponent<Sprite>(Size2i(4 * 2, 4));

		start();
	}

	void start()
	{
		memset(map, 0, sizeof(map));
		
		// 生成初始的两个数字
		generate(2, 2);
		generate(2, 2);

		moveLeft();

		show();
	}

	void moveLeft()
	{
		for(int y = 0; y < 4; y++)
			for(int x = 1; x < 4; x++)
				;
	}

	void generate(int a, int b)
	{
		while(true)
		{
			auto p = random.getPoint2i({0, 0}, {3, 3});
			if(map[p.x][p.y] == 0)
			{
				map[p.x][p.y] = random.getUint32(0, 1) ? a : b;
				break;
			}
		}
	}

	void show()
	{
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++)
				if(map[x][y])
					sprite->drawPoint({x * 2, y}, Tile('0' + map[x][y], map[x][y]  % Color::max));
				else
					sprite->drawPoint({x * 2, y}, Tile('.', map[x][y] % Color::max));
	}

private:
	char              map[4][4];
	Sprite*           sprite;
	Random            random;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* CreateApplication()
{
	return new Game2048;
}