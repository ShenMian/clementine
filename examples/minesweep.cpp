// Copyright 2021 SMS
// License(Apache-2.0)

#include "Clem.h"

using namespace std;

constexpr int board_size_x = 9;
constexpr int board_size_y = 9;
const Size    board_size   = {board_size_x, board_size_y};
const int     mine_num     = 10;

class Minesweep : public Application
{
public:
	Minesweep()
			: Application("Minesweep")
	{
		scene = make_shared<Scene>();
		pushScene(scene);

		memset(map, '0', sizeof(map));

		int i = mine_num;
		do
		{
			auto p = random.getPoint({0, 0}, {board_size.x - 1, board_size.y - 1});
			if(map[(int)p.x][(int)p.y] == '*')
				continue;
			map[(int)p.x][(int)p.y] = '*';
			for(int x = -1; x <= 1; x++)
				for(int y = -1; y <= 1; y++)
					if(inBoard((int)p.x + x, (int)p.x + x) && map[(int)p.x + x][(int)p.y + y] != '*')
						map[(int)p.x + x][(int)p.y + y]++;
		} while(--i);

		const Size spriteSize = {board_size.x * 2 + 1, board_size.y + 2};

		auto board = scene->createEntity("board");
		sprite     = &board.addComponent<Sprite>(spriteSize);
		sprite->drawRect(Rect({0, 0}, {board_size.x * 2, board_size.y + 1}), Tile('#'));

		EventDispatcher::getInstance().addListener(Event::Type::mouse, [&](Event* e) {
			auto event = dynamic_cast<MouseEvent*>(e);
			if(event->getType() == MouseEvent::Type::click)
			{
				auto p = event->getPosition();
				p      = {((p.x + 1) / 2) - 1, p.y - 1};
				if(event->getKey() == MouseEvent::Key::left_buttom)
					open(p.x, p.y);
				else
					flag(p.x, p.y);
			}
		});
	}

	~Minesweep()
	{
		puts("GAME OVER");
		getchar();
	}

	void open(int x, int y)
	{
		if(!inBoard(x, y) || map[x][y] == '.')
			return;

		if(map[x][y] == '*')
			stop();

		if(map[x][y] == '0')
		{
			map[x][y] = '.';
			for(int x_ = -1; x_ <= 1; x_++)
				for(int y_ = -1; y_ <= 1; y_++)
					open(x + x_, y + y_);
		}

		sprite->drawPoint(1 + x * 2, 1 + y, Tile(map[x][y], map[x][y] % Color::max));

		map[x][y] = '.';
	}

	void flag(int x, int y)
	{
		if(!inBoard(x, y) || map[x][y] == '.')
			return;

		auto flag = find(flags.begin(), flags.end(), Point(x, y));
		if(flag == flags.end())
		{
			sprite->drawPoint(1 + x * 2, 1 + y, Tile('?', Color::yellow));
			flags.push_back(Point(x, y));
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
	Sprite*           sprite;
	char              map[board_size_x][board_size_y];
	vector<Point>     flags;
	Random            random;
	shared_ptr<Scene> scene;
};

Application* CreateApplication()
{
	return new Minesweep;
}
