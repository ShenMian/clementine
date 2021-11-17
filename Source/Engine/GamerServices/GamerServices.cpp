// Copyright 2021 ShenMian
// License(Apache-2.0)


#include "GamerServices.h"
#include <cassert>
#include <exception>
#include <steam/steam_api.h>

namespace
{

Player::State SteamState(EPersonaState state)
{
    switch(state)
    {
    case k_EPersonaStateOffline:
        return Player::State::Offline;
        break;

    case k_EPersonaStateOnline:
    case k_EPersonaStateBusy:
    case k_EPersonaStateAway:
    case k_EPersonaStateSnooze:
        return Player::State::Online;
        break;

    default:
        assert(false);
    }
    return Player::State::Offline;
}

}

inline Player              GamerServices::player;
inline std::vector<Player> GamerServices::friends;

void GamerServices::update()
{
    SteamAPI_RunCallbacks();
}

const Player& GamerServices::getPlayer()
{
    return player;
}

void GamerServices::init()
{
    if(!SteamAPI_Init())
        throw std::exception("steam api init failed");

    const auto id = SteamUser()->GetSteamID().ConvertToUint64();
    const auto name = SteamFriends()->GetPersonaName();
    player = {id, name, Player::State::Online};

    const auto count = SteamFriends()->GetFriendCount(k_EFriendFlagAll);
    for(int i = 0; i < count; i++)
    {
        const auto id   =  SteamFriends()->GetFriendByIndex(i, k_EFriendFlagAll).ConvertToUint64();
        const auto name =  SteamFriends()->GetFriendPersonaName(id);
        const auto state = SteamState(SteamFriends()->GetFriendPersonaState(id));

        friends.emplace_back(id, name, state);
    }
    friends.shrink_to_fit();
}

void GamerServices::deinit()
{
    SteamAPI_Shutdown();
}
