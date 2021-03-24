// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"

#include <iostream>

using namespace std;

// Easy
constexpr int board_size_x = 9;
constexpr int board_size_y = 9;
const int     mine_num     = 10;

// Middle
/*
constexpr int board_size_x = 16;
constexpr int board_size_y = 16;
const int     mine_num     = 40;
*/

const Vec2<float> board_size = {board_size_x, board_size_y};

class Minesweep : public Application
{
public:
	Minesweep()
			: Application("Minesweep"), scene(make_shared<Scene>())
	{
		pushScene(scene);

		memset(map, '0', sizeof(map));

		int i = mine_num;
		do
		{
			Vec2<int> p = random.getPoint({0, 0}, {board_size.x - 1, board_size.y - 1});
			if(map[(int)p.x][(int)p.y] == '*')
				continue;
			map[(int)p.x][(int)p.y] = '*';
			for(int x = -1; x <= 1; x++)
				for(int y = -1; y <= 1; y++)
					if(inBoard((int)p.x + x, (int)p.x + x) && map[(int)p.x + x][(int)p.y + y] != '*')
						map[(int)p.x + x][(int)p.y + y]++;
		} while(--i);

		auto board = scene->createEntity("board");
		sprite     = &board.addComponent<Sprite>(Size(board_size.x * 2 + 1, board_size.y + 2));
		sprite->drawRect(Rect({0, 0}, {board_size.x * 2, board_size.y + 1}), Tile('#'));

		EventDispatcher::getInstance().addListener(Event::Type::mouse, [&](Event* e) {
			auto event = dynamic_cast<MouseEvent*>(e);
			if(event->getType() == MouseEvent::Type::click)
			{
				Vec2<int> p = event->getPosition();
				p      = {((p.x + 1) / 2) - 1, p.y - 1};
				if(event->getKey() == MouseEvent::Key::left_buttom)
					open(p.x, p.y);
				else
					flag(p.x, p.y);
			}
		});

		surplus = board_size.area() - mine_num;
	}

	void lost()
	{
		for(int x = 0; x < board_size.x; x++)
			for(int y = 0; y < board_size.x; y++)
				if(map[x][y] == '*')
					sprite->drawPoint(1 + x * 2, 1 + y, Tile('*', Color::red));
		(void)getchar();
		stop();
	}

	void win()
	{
		wstring str = L"-=[ You won ]=-";
		sprite->drawString({(board_size.x * 2 + 1 - str.size()) / 2, board_size.y / 2}, str, Color::yellow);
		(void)getchar();
		stop();
	}

	void open(int x, int y)
	{
		if(!inBoard(x, y) || map[x][y] == '.')
			return;

		if(map[x][y] == '*')
			lost();

		if(map[x][y] == '0')
		{
			map[x][y] = '.';
			for(int x_ = -1; x_ <= 1; x_++)
				for(int y_ = -1; y_ <= 1; y_++)
					open(x + x_, y + y_);
		}

		sprite->drawPoint(1 + x * 2, 1 + y, Tile(map[x][y], map[x][y] % Color::max));

		map[x][y] = '.';

		surplus--;
		if(surplus == 0)
			win();
	}

	void flag(int x, int y)
	{
		if(!inBoard(x, y) || map[x][y] == '.')
			return;

		auto flag = find(flags.begin(), flags.end(), Point<int>(x, y));
		if(flag == flags.end())
		{
			sprite->drawPoint(1 + x * 2, 1 + y, Tile('?', Color::yellow));
			flags.push_back(Point<int>(x, y));
		}
		else
		{
			sprite->drawPoint(1 + x * 2, 1 + y, Tile(' '));
			flags.erase(flag);
		}
	}

	bool inBoard(int x, int y)
	{
		return x >= 0 && x < board_size.x && y >= 0 && y < board_size.y;
	}

private:
	int                surplus;
	char               map[board_size_x][board_size_y];
	Sprite*            sprite;
	vector<Point<int>> flags;
	Random             random;
	shared_ptr<Scene>  scene;
};

Application* CreateApplication()
{
	return new Minesweep;
}
