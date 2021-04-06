// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
using namespace clem;

class MyScript : public Script
{
	void update(float) override
	{
		Assert::isTrue(false, CALL_INFO);
	}
};

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
		board.getComponent<Transform>().setLocalPosition({3, 1});
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
		{
			;
		}
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
				sprite->drawPoint({x * 2, y},
													Tile(map[x][y] ? '0' + map[x][y] : '.', map[x][y] % Color::max));
	}

private:
	char              map[4][4];
	Sprite*           sprite;
	Random            random;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new Game2048;
}
