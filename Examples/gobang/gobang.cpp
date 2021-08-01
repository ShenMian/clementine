// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem.h>

using namespace std;
using namespace clem;

Server server;

enum Chess : uint8_t
{
	none,
	black,
	white
};

enum class NetCommand
{
	place
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

		server.onAccept = [this](shared_ptr<Connection> conn) {
			conn->read<NetCommand>();
			return true;
		};
		server.onMessage = [this](shared_ptr<Connection> conn) {
			auto& msg = conn->getMessage<NetCommand>();

			int   x, y;
			Chess c;

			switch(msg.header.id)
			{
			case NetCommand::place:
				msg >> c >> y >> x;
				this->map[x][y] = c;
				show();
				break;

			default:
				abort();
			}
		};
		server.onError = [this](shared_ptr<Connection> conn, error_code ec) {
			printf("%s", ec.message().c_str());
		};
		server.start(25565);

		client.onError = [](error_code ec) {
			printf("%s", ec.message().c_str());
		};
		client.connect("127.0.0.1", 25565);

		scene->createEntity("board").addComponent<Sprite>(Size2i(15 * 2, 15));

		EventDispatcher::get().addListener(Event::Type::mouse, [&](Event* e) {
			auto event = dynamic_cast<MouseEvent*>(e);
			if(event->getType() == MouseEvent::Type::click)
			{
				Point2i p = event->getPosition();
				place(p.x / 2, p.y, Chess::black);
			}
		});

		memset(map, 0, sizeof(map));

		show();
	}

	void place(int x, int y, Chess c)
	{
		Assert::isTrue(0 <= x && x <= 15 && 0 <= y && y <= 15, "out of range");
		if(map[x][y] != Chess::none)
			return;

		// map[x][y] = c;

		Message msg(NetCommand::place);
		msg << x << y << c;
		client.write(msg);
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
	Client            client;
	shared_ptr<Scene> scene = make_shared<Scene>();
};

Application* clem::CreateApplication()
{
	return new App;
}