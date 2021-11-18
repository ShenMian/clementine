// Copyright 2021 ShenMian
// License(Apache-2.0)


#include "GamerServices.h"
#include <cassert>
#include <exception>
#include <steam/steam_api.h>

#include "Steam/SteamGamerServices.h"
#include <thread>

namespace
{

Player::State SteamState(EPersonaState state)
{
    switch(state)
    {
    case k_EPersonaStateOffline:
        return Player::State::Offline;

    case k_EPersonaStateOnline:
    case k_EPersonaStateBusy:
    case k_EPersonaStateAway:
    case k_EPersonaStateSnooze:
    case k_EPersonaStateLookingToTrade:
    case k_EPersonaStateLookingToPlay:
        return Player::State::Online;

    default:
        assert(false);
    }
    return Player::State::Offline;
}

}

inline std::string         GamerServices::appName;
inline Player              GamerServices::player;
inline std::vector<Player> GamerServices::friends;

void GamerServices::update()
{
    SteamAPI_RunCallbacks();
}

const Player& GamerServices::getLocalPlayer()
{
    return player;
}

const std::vector<Player>& GamerServices::getFriends()
{
    return friends;
}

const std::string& GamerServices::getAppName()
{
    return appName;
}

void GamerServices::init()
{
    if(!SteamAPI_Init())
        throw std::exception("steam api init failed");

    if(!SteamUser()->BLoggedOn())
        throw std::exception("steam user is not logged in");

    // if(!SteamInput()->Init(true))
    //     throw std::exception("steam input init failed");

    SteamNetworkingUtils()->InitRelayNetworkAccess();

    SteamMatchmaking()->RequestLobbyList();

    SteamGamerServices instance;

    /*SteamRelayNetworkStatus_t detal;
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));

        auto ret = SteamNetworkingUtils()->GetRelayNetworkStatus(&detal);
        puts(detal.m_debugMsg);
        if(detal.m_eAvail == k_ESteamNetworkingAvailability_Current)
            break;
    }*/

    appName.resize(128);
    SteamAppList()->GetAppName(SteamUtils()->GetAppID(), appName.data(), 128);
    appName.resize(appName.size());

    const auto id = SteamUser()->GetSteamID().ConvertToUint64();
    const auto name = SteamFriends()->GetPersonaName();
    player = { id, name, Player::State::Online };

    const auto count = SteamFriends()->GetFriendCount(k_EFriendFlagAll);
    for(int i = 0; i < count; i++)
    {
        const auto id = SteamFriends()->GetFriendByIndex(i, k_EFriendFlagAll).ConvertToUint64();
        const auto name = SteamFriends()->GetFriendPersonaName(id);
        const auto state = SteamState(SteamFriends()->GetFriendPersonaState(id));

        friends.emplace_back(id, name, state);
    }
    friends.shrink_to_fit();

    /*
    Player remote;

    for(auto& player : friends)
        printf("%-10s %s\n", player.getName().c_str(), player.getState() == Player::State::Offline ? "Off" : "On");
    puts(getLocalPlayer().getName().c_str());

    do
    {
        printf("Please input the user name: ");
        char input[125] = { '\0' };
        scanf("%s", input);
        std::string username(input);
        for(auto& player : friends)
            if (username == player.getName())
            {
                remote = player;
                break;
            }
            else if (username == getLocalPlayer().getName())
            {
                remote = getLocalPlayer();
                break;
            }
    } while(remote == Player());

    SteamNetworkingSockets()->CreateListenSocketP2P(0, 0, nullptr);

    SteamNetworkingIdentity identity;
    identity.SetSteamID(remote.getId());
    auto conn = SteamNetworkingSockets()->ConnectP2P(identity, 0, 0, nullptr);
    if (conn == k_HSteamNetConnection_Invalid)
        assert(false && "连接失败");

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::string msg = "Hello World!";
        int64_t msgNum;
        auto ret = SteamNetworkingSockets()->SendMessageToConnection(conn, reinterpret_cast<void*>(msg.data()), msg.size(), k_nSteamNetworkingSend_Reliable, &msgNum);
        if(ret != k_EResultOK)
            if(ret == k_EResultNoConnection)
                printf("Error: no/failed network connection\n");

        if(msgNum)
            printf("-> %10s: %s\n", getLocalPlayer().getName().c_str(), msg.c_str());

        SteamNetworkingMessage_t* msgs[32];
        int num = SteamNetworkingSockets()->ReceiveMessagesOnConnection(conn, msgs, 32);
        for(int i = 0; i < num; i++)
        {
            auto msg = msgs[i];
            auto size = msg->GetSize();

            Player remote;
            for(auto& player : friends)
                if(player.getId() == msg->GetConnectionUserData())
                {
                    remote = player;
                    break;
                }

            printf("<- %10s: %s\n", remote.getName().c_str(), reinterpret_cast<const char*>(msg->GetData()));
        }
    }*/
}

void GamerServices::deinit()
{
    SteamAPI_Shutdown();
}
