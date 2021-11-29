// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "Achievement.h"
#include <steam/steam_api.h>

void Achievement::unlock()
{
	SteamUserStats()->SetAchievement("Ach_WIN_ONE_GAME");
}

void Achievement::init()
{
	SteamUserStats()->RequestCurrentStats();
}
