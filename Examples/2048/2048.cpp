// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
using namespace clem;

class App : public Application
{
public:
	App()
			: Application("2048")
	{
	}

	void init() override
	{
		pushScene(scene);

		auto& board = scene->createEntity("board");
		board.getComponent<Transform>().setPosition({0, 0});
		sprite = &board.addComponent<Sprite>(Size2i(4 * 5, 4 * 2));

		board.addComponent<Script>().onUpdate = [&](float dt) {
			static float lag = 0;
			lag += dt;
			if(lag < 0.1)
				return;
			lag = 0;

			if(Keyboard::getKeyState(Keyboard::Key::A))
			{
				if(moveLeft())
					generate({2});
			}

			show();
		};

		start();
	}

	void start()
	{
		memset(map, 0, sizeof(map));

		// 生成初始的两个数字
		generate({2});
		generate({2});
	}

	bool moveLeft()
	{
		bool moved = false;
		for(int y = 0; y < 4; y++)
			for(int x = 0; x < 4 - 1; x++)
				if(map[x][y] == 0)
				{
					for(int i = x + 1; i < 4; i++)
						if(map[i][y] != 0)
						{
							map[x][y] = map[i][y];
							map[i][y] = 0;
							moved     = true;
							break;
						}
				}
				else
				{
					for(int i = x + 1; i < 4; i++)
						if(map[i][y] == map[x][y])
						{
							map[x][y] *= 2;
							map[i][y] = 0;
							moved     = true;
							break;
						}
				}
		return moved;
	}

	bool isFull()
	{
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++)
				if(map[x][y] == 0)
					return false;
		return true;
	}

	// 在随机位置上生成一个传入参数中的随机一个数
	void generate(const vector<int>& nums)
	{
		while(true)
		{
			auto pos = random.getPoint2i({0, 0}, {3, 3});
			if(map[pos.x][pos.y] != 0)
				continue;
			map[pos.x][pos.y] = nums[random.getUint32(0, (uint32_t)nums.size() - 1)];
			break;
		}
	}

	void show()
	{
		for(int x = 0; x < 4; x++)
			for(int y = 0; y < 4; y++)
				sprite->drawString({x * 5, y * 2}, to_wstring(map[x][y]), map[x][y] % Color::max);
	}

private:
	int               map[4][4];
	Sprite*           sprite;
	Random            random;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}
