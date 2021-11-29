// Copyright 2021 ShenMian
// License(Apache-2.0)

#include "SteamGamerServices.h"

SteamGamerServices::SteamGamerServices()
	: callbackUserStatsReceived(this, &SteamGamerServices::onUserStatsReceived)
{
	requestStatsAsync();
}

void SteamGamerServices::requestStatsAsync()
{
	SteamUserStats()->RequestCurrentStats();
}

void SteamGamerServices::onUserStatsReceived(UserStatsReceived_t* data)
{
	if(data == nullptr || data->m_eResult != EResult::k_EResultOK)
		return;

	printf("RECVED!");
}
