// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Player.hpp"
#include <vector>

class Player;
class Achievement;

class GamerServices
{
public:
    static void update();

    static const Player& getLocalPlayer();

    static const std::vector<Player>& getFriends();

    static const std::string& getAppName();

    static void init();
    static void deinit();

private:
    static Player              player;
    static std::vector<Player> friends;

    static std::string appName;
};
