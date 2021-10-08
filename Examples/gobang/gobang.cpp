// Copyright 2021 SMS
// License(Apache-2.0)

#include <Clem/Clem.h>

using namespace std;
using namespace clem;

Server server;

enum Chess : uint8_t
{
    none,
    black,
    white
};

enum class Command
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
        server.onAccept = [this](shared_ptr<Connection> conn)
        {
            conn->read<Command>();
            return true;
        };

        server.onMessage = [this](shared_ptr<Connection> conn)
        {
            auto& msg = conn->getMessage<Command>();

            int   x, y;
            Chess c;

            switch(msg.header.id)
            {
            case Command::place:
                msg >> c >> y >> x;
                this->map[x][y] = c;
                refresh();
                break;

            default:
                abort();
            }
        };

        server.onError = [this](shared_ptr<Connection> conn, error_code ec)
        {
            printf("%s", ec.message().c_str());
        };

        server.start(25565);


        client.onError = [](error_code ec)
        {
            printf("%s", ec.message().c_str());
        };

        client.connect("127.0.0.1", 25565);
        place(0, 0, Chess::black);

        /*
        Main::registry.create("board").add<Sprite>(Size2i(15 * 2, 15));

        EventDispatcher::get().addListener(Event::Type::mouse, [&](Event* e)
                                           {
                                               auto event = dynamic_cast<MouseEvent*>(e);
                                               if(event->getType() == MouseEvent::Type::click)
                                               {
                                                   Point2i p = event->getPosition();
                                                   place(p.x / 2, p.y, Chess::black);
                                               }
                                           });

        memset(map, 0, sizeof(map));

        show();
        */
    }

    void place(int x, int y, Chess c)
    {
        Assert::isTrue(0 <= x && x <= 15 && 0 <= y && y <= 15, "out of range");
        Assert::isTrue(map[x][y] != Chess::none);

        map[x][y] = c;

        Message msg(Command::place);
        msg << x << y << c;
        client.write(msg);
        refresh();
    }

    void refresh()
    {
        const char tiles[] = {'.', 'X', 'O'};
        auto&      sprite  = Main::registry.create("board").get<Sprite>();
        for(int x = 0; x < 15; x++)
            for(int y = 0; y < 15; y++)
                sprite.drawPoint(x * 2, y, tiles[map[x][y]]);
    }

private:
    int    map[15][15];
    Client client;
};

Application* clem::CreateApplication()
{
    return new App;
}