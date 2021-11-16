// Copyright 2021 ShenMian
// License(Apache-2.0)


#include "GamerServices.h"
#include <exception>
#include <steam/steam_api.h>

void GamerServices::update()
{
    SteamAPI_RunCallbacks();
}

void GamerServices::init()
{
    if(!SteamAPI_Init())
        throw std::exception("steam api init failed");

    auto name = SteamFriends()->GetPersonaName();
}

void GamerServices::deinit()
{
    SteamAPI_Shutdown();
}
