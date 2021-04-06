// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
using namespace clem;

// TODO: 双缓冲

class Sort : public Application
{
public:
	Sort()
			: Application("Sort")
	{
	}

	void init() override
	{
		pushScene(scene);

		auto entity = scene->createEntity();
		entity.getComponent<Transform>().setLocalPosition({1, 1});
		sprite = &entity.addComponent<Sprite>(size);

		// 生成随机数
		for(int i = 0; i < size.x; i++)
			data.push_back(random.getUint32(1, size.y));

		// 启动排序线程
		static std::thread thread(&Sort::sort, this);
		thread.detach();
	}

	// 排序算法
	void sort()
	{
		for(int i = 0; i < data.size() - 1; i++)
		{
			for(int j = i + 1; j < data.size(); j++)
				if(data[i] > data[j])
				{
					swap(data[i], data[j]);
					showSwap(i, j);
				}
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		showDone();
	}

	// 展示交换
	void showSwap(int a, int b)
	{
		sprite->clear();
		for(int i = 0; i < data.size(); i++)
			sprite->fillRect(Rect2i({1 * i, size.y - data[i]}, {1, data[i]}),
											 Tile(' ', i == a || i == b ? blue : white));
	}

	// 展示结果
	void showDone()
	{
		showSwap(-1, -1);
		sprite->fillRect(Rect2i({0, size.y - data[0]}, {1, data[1]}), Tile(' ', green));
		for(int i = 1; i < data.size(); i++)
		{
			if(data[i - 1] <= data[i])
				sprite->fillRect(Rect2i({1 * i, size.y - data[i]}, {1, data[i]}), Tile(' ', green));
			else
				sprite->fillRect(Rect2i({1 * i, size.y - data[i]}, {1, data[i]}), Tile(' ', red));
			this_thread::sleep_for(chrono::milliseconds(8));
		}
	}

private:
	Size2i            size = {118, 28};
	vector<int>       data;
	Sprite*           sprite = nullptr;
	Random            random;
	Color             white = Color(Color::white, Color::white);
	Color             green = Color(Color::green, Color::green);
	Color             blue  = Color(Color::blue, Color::blue);
	Color             red   = Color(Color::red, Color::red);
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new Sort;
}
