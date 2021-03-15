// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "clem.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	Log::init();
	PROFILE_SESSION_BEGIN();
	Main main(argc, argv);
	PROFILE_SESSION_END();
	return 0;
}

Main::Main(int argc, char* argv[])
{
	initialize();
}

void Main::initialize()
{
	PROFILE_FUNC();

	PROFILE_SCOPE_BEGIN(sdl_init);
	// ≥ı ºªØ SDL
	auto ret = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS);
	if(ret == -1)
	{
		CLEM_CORE_ERROR("Initialize SDL failed");
	}
	PROFILE_SCOPE_END(sdl_init);
}
