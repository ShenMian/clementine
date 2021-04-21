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

		scene->createEntity("board").addComponent<Sprite>(Size2i(15 * 2, 15)).setDepth(1);

		auto cursor = scene->createEntity("cursor");
		cursor.addComponent<Sprite>(Size2i(1, 1));
		cursor.addComponent<Script>().onUpdate = [&](float dt) {
			auto  cursor = scene->getEntity("cursor");
			auto& sprite = cursor.getComponent<Sprite>();
			auto& tf     = cursor.getComponent<Transform>();

			static float lag    = 0;
			lag += dt;
			sprite.drawPoint(0, 0, '+');
			if(lag >= 2)
				lag = 0;

			if(Keyboard::getKeyState(Keyboard::Key::W))
				tf.setLocalPosition(tf.getLocalPosition() + Vector2::up);
			else if(Keyboard::getKeyState(Keyboard::Key::S))
				tf.setLocalPosition(tf.getLocalPosition() + Vector2::down);
			else if(Keyboard::getKeyState(Keyboard::Key::A))
				tf.setLocalPosition(tf.getLocalPosition() + Vector2::left);
			else if(Keyboard::getKeyState(Keyboard::Key::D))
				tf.setLocalPosition(tf.getLocalPosition() + Vector2::right);

			show();
		};

		memset(map, 0, sizeof(map));

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
