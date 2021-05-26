// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>
#include <future>
#include <iostream>
#include <limits.h>

using namespace std;
using namespace clem;

// TODO: UI: ʣ������, ��ʱ, ��ʼ�˵�(�Ѷ�ѡ��)
//       �Ƚҿ���һ�����������ɵ���, ��ֹ��һ�ξʹ���������

class App : public Application
{
public:
	App()
			: Application("Minesweeper")
	{
	}

	void init() override
	{
		pushScene(scene);

		opening.loadFromFile("assets/opening.wav");
		explode.loadFromFile("assets/explode.wav");

		// TODO: UI
		puts("/--[Level]--\\\n"
				 "| 1. Easy   |\n"
				 "| 2. Middle |\n"
				 "| 3. Hard   |\n"
				 "\\-----------/");
		char choice = getchar();
		(void)getchar();
		switch(choice)
		{
		default:
		case '1':
			board_size.x = 9;
			board_size.y = 9;
			mine_num     = 10;
			break;

		case '2':
			board_size.x = 16;
			board_size.y = 16;
			mine_num     = 40;
			break;

		case '3':
			board_size.x = 30;
			board_size.y = 16;
			mine_num     = 99;
			break;
		}

		auto board = scene->createEntity("board");
		sprite     = &board.addComponent<Sprite>(Size2i(board_size.x * 2 + 1, board_size.y + 2));

		EventDispatcher::get().addListener(Event::Type::mouse, [&](Event* e) {
			auto event = dynamic_cast<MouseEvent*>(e);
			if(event->getType() == MouseEvent::Type::click)
			{
				Point2i p = event->getPosition();
				p         = {((p.x + 1) / 2) - 1, p.y - 1};
				if(event->getKey() == MouseEvent::Key::left_buttom)
					open(p.x, p.y);
				else if(event->getKey() == MouseEvent::Key::right_buttom)
					flag(p.x, p.y);
			}
		});

		/*auto ui = scene->createEntity("info");
		ui.addComponent<Sprite>(Size2i(15, board_size.y + 2));
		// FIXME: ����ʵ�������ᱻ�ͷ�
		ui.getComponent<Transform>().setLocalPosition(Point2((float)board_size.x * 2 + 2, 0));

		ui.addComponent<Script>().onUpdate = [&](float) {
			auto& s = scene->getEntityByTag("info").getComponent<Sprite>();
			s.drawString({0, 0}, L"Mines: " + to_wstring(mine_num - flags.size()));
		};*/

		start();
	}

	void start()
	{
		memset(map, '0', sizeof(map));
		for(int i = 0; i < mine_num; i++)
		{
			Point2i p = random.getPoint2i({0, 0}, {board_size.x - 1, board_size.y - 1});
			if(map[p.x][p.y] == '*')
			{
				i--;
				continue;
			}
			map[p.x][p.y] = '*';
			for(int x = -1; x <= 1; x++)
				for(int y = -1; y <= 1; y++)
					if(inBoard(p.x + x, p.y + y) && map[p.x + x][p.y + y] != '*')
						map[p.x + x][p.y + y]++;
		}

		flags.clear();

		sprite->clear();
		sprite->drawRect(Rect2i({0, 0}, {board_size.x * 2 + 1, board_size.y + 2}), Tile('#'));

		surplus = board_size.area() - mine_num;

		source.play(opening);
	}

	void win()
	{
		wstring str = L"-=[ You won ]=-";
		sprite->drawString({(board_size.x * 2 + 1 - (int)str.size()) / 2, board_size.y / 2}, str, Color::yellow);

		static auto h = async([&]() {
			(void)getchar();
			stop();
		});
	}

	void lost()
	{
		source.play(explode);

		for(int x = 0; x < board_size.x; x++)
			for(int y = 0; y < board_size.y; y++)
				if(map[x][y] == '*')
					sprite->drawPoint(x * 2 + 1, y + 1, Tile('*', Color::red));

		wstring str = L"Press enter to exit";
		sprite->drawString({(board_size.x * 2 + 1 - (int)str.size()) / 2, 0}, str, Color::red);
		
		static auto h = async([&]() {
			(void)getchar();
			stop();
		});
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
			for(int i = -1; i <= 1; i++)
				for(int j = -1; j <= 1; j++)
					open(x + i, y + j);
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

		auto flag = find(flags.begin(), flags.end(), Point2i(x, y));
		if(flag == flags.end())
		{
			sprite->drawPoint(1 + x * 2, 1 + y, Tile('?', Color::yellow));
			flags.push_back(Point2i(x, y));
		}
		else
		{
			sprite->drawPoint(1 + x * 2, 1 + y, Tile(' '));
			flags.erase(flag);
		}
	}

private:
	bool inBoard(int x, int y) const
	{
		return x >= 0 && x < board_size.x && y >= 0 && y < board_size.y;
	}

	Size2i            board_size;		// ������С
	int               mine_num;			// ��������
	char              map[30][16];	// ����
	int               surplus;			// ʣ��δ�ҿ�����
	vector<Point2i>   flags;        // ���λ��
	Sound             opening;			// ������Ч(��Ϸ��ʼ)
	Sound             explode;			// ����������Ч(��Ϸʧ��)
	Source            source;
	Random            random;
	Sprite*           sprite;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}