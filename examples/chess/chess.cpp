// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
using namespace clem;

enum Chess
{
	none,
	black,
	white
};

class App : public Application
{
public:
	App()
			: Application("Gobang")
	{
	}

	void init() override
	{
		pushScene(scene);

		auto& board = scene->createEntity("board").addComponent<Sprite>(Size2i(15 * 2, 15));
		board.setDepth(1);

		memset(map, 0, sizeof(map));

		auto cursor = scene->createEntity("cursor");
		cursor.addComponent<Sprite>(Size2i(3, 3));
		cursor.addComponent<Script>().onUpdate = [&](float dt) {
			static auto  cursor    = scene->getEntity("cursor");
			static auto& sprite    = cursor.getComponent<Sprite>();
			static auto& transform = cursor.getComponent<Transform>();
			static float lag = 0;
			lag += dt;
			if(lag >= 1)
			{
				sprite.drawPoint(transform.getPosition(), '+');
				lag = 0;
			}

			if(Keyboard::getKeyState(Keyboard::Key::W))
				;
		};

		show();
	}

	void show()
	{
		const char tiles[] = {'.', 'X', 'O'};
		auto&      sprite  = scene->getEntity("board").getComponent<Sprite>();
		for(int x = 0; x < 15; x++)
			for(int y = 0; y < 15; y++)
				sprite.drawPoint(x * 2, y, tiles[map[x][y]]);
	}

private:
	int               map[15][15];
	Random            random;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}
