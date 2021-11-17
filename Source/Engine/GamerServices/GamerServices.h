// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Player.hpp"
#include <string_view>
#include <vector>

class Player;

class GamerServices
{
public:
    static void update();

    static const Player& getPlayer();

    static void init();
    static void deinit();

private:
    static Player              player;
    static std::vector<Player> friends;
};
