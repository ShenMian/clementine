// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

#include <iostream>

using namespace std;

class Unnamed : public Application
{
public:
	void init() override
	{
		pushScene(scene);

		auto  figure = scene->createEntity("figure");
		auto& sprite = figure.addComponent<Sprite>(Size2i(50, max));
		figure.getComponent<Transform>().setLocalPosition({6, 3});

		for(int i = 0; i < 50; i++)
			data.push_back(random.getUint32(1, max));

		figure.addComponent<Script>().onUpdate = [&](float) {
			data.insert(data.begin(), random.getUint32(1, max));
			data.pop_back();

			sprite.clear();
			for(int i = 0; i < data.size(); i++)
				sprite.fillRect(Rect2i({1 * i, max - data[i]}, {1, data[i]}), Tile('#', data[i] % Color::max));
		};

		setMsPerUpdate(32);
	}

private:
	const int         max = 10;
	vector<int>       data;
	Random            random;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* CreateApplication()
{
	return new Unnamed;
}
