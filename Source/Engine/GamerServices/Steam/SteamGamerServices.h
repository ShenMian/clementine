// Copyright 2021 ShenMian
// License(Apache-2.0)

#pragma once

#include "../GamerServices.h"
#include <steam/steam_api.h>

class SteamGamerServices : public GamerServices
{
public:
    SteamGamerServices();

private:
    void requestStatsAsync();

    STEAM_CALLBACK(SteamGamerServices, onUserStatsReceived, UserStatsReceived_t, callbackUserStatsReceived);
    // STEAM_CALLBACK(SteamGamerServices, OnUserStatsStored, UserStatsStored_t, callbackUserStatsStored);
    // STEAM_CALLBACK(SteamGamerServices, OnAchievementStored,UserAchievementStored_t, callbackAchievementStored);
};