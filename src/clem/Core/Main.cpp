// Copyright 2021 SMS
// License(Apache-2.0)

#include "Main.h"
#include "Application.h"
#include "clem.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	return Main::entrypoint(argc, argv);
}

int Main::entrypoint(int argc, char* argv[])
{
	initialize();

	Application app;

	return 0;
}

void Main::initialize()
{
	Log::init();

	PROFILE_SESSION_BEGIN();

	PROFILE_FUNC();

	// width / height = 80 / 25 => width * 25 = height * 80
	const short width  = 80;
	const short height = width * 25 / 80;
	frameBuffer.setSize({width, height});

#ifdef OS_WIN
	// 开启 VT100 模式
	const auto hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD      mode;
	if(!GetConsoleMode(hStdOut, &mode))
		assert(false);
	if(!SetConsoleMode(hStdOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
		assert(false);
#endif

	/*
	PROFILE_SCOPE_BEGIN(sdl_init);
	// 初始化 SDL
	auto ret = SDL_Init(SDL_INIT_AUDIO | SDL_INIT_JOYSTICK | SDL_INIT_EVENTS);
	if(ret == -1)
	{
		CLEM_CORE_ERROR("Initialize SDL failed");
	}
	PROFILE_SCOPE_END(sdl_init);
	*/
}
