// Copyright 2021 SMS
// License(Apache-2.0)

#include "Keyboard.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Logger.h"
#include "Platform.h"
#include "Profiler.h"
#include "Input.h"
#include <cassert>

#ifdef OS_UNIX
#	include <termios.h>
#	include <unistd.h>
#endif

namespace clem
{
std::unordered_map<Keyboard::Key, bool> Keyboard::states;

bool Keyboard::getState(Key k)
{
	if(states.find(k) != states.end())
		return states[k];
	else
		return false;
}

void Keyboard::setState(Key k, bool s)
{
	states[k] = s;
}

#ifdef OS_UNIX

void Keyboard::update()
{
	PROFILE_FUNC();

	char ch = -1;
	ch      = getchar();
	if(ch == -1)
		return;
	auto vk = ch; // ASCII -> VK
	Keyboard::setState((Keyboard::Key)vk, true);
}

void Keyboard::init()
{
	PROFILE_FUNC();
	CLEM_LOG_INFO("core", "keyboard init");

	termios opts;
	tcgetattr(0, &opts);          // grab old terminal i/o settings
	opts.c_lflag &= ~ICANON;      // disable buffered i/o
	opts.c_lflag &= ~ECHO;        // set echo mode
	tcsetattr(0, TCSANOW, &opts); // use these new terminal i/o settings now
}

void Keyboard::deinit()
{
	PROFILE_FUNC();
	CLEM_LOG_INFO("core", "keyboard deinit");

	termios opts;
	tcgetattr(0, &opts);
	opts.c_lflag &= ICANON;
	opts.c_lflag &= ECHO;
	tcsetattr(0, TCSANOW, &opts);
}

#endif

#ifdef OS_WIN

void Keyboard::update()
{
	PROFILE_FUNC();

	static HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	static DWORD  res;
	DWORD         numOfEvents;
	GetNumberOfConsoleInputEvents(hIn, &numOfEvents);
	if(numOfEvents < 1 && inputRecords.empty())
		return;
	const auto& offset = inputRecords.size();
	inputRecords.resize(inputRecords.size() + numOfEvents);
	ReadConsoleInput(hIn, inputRecords.data() + offset, numOfEvents, &res);

	for(const auto& record : inputRecords)
	{
		if(record.EventType != KEY_EVENT)
			continue;

		const KEY_EVENT_RECORD* keyRecord = &record.Event.KeyEvent;
		Keyboard::setState((Keyboard::Key)keyRecord->wVirtualKeyCode, keyRecord->bKeyDown);
		/*EventDispatcher::get().dispatch(
				KeyEvent(keyRecord->wVirtualKeyCode,
								 keyRecord->bKeyDown,
								 keyRecord->wRepeatCount));*/
	}

	for(size_t i = 0; i < inputRecords.size(); i++)
		if(inputRecords[i].EventType == KEY_EVENT)
			inputRecords.erase(inputRecords.begin() + i);
}

void Keyboard::init()
{
	PROFILE_FUNC();
	CLEM_LOG_INFO("core", "keyboard init");
}

void Keyboard::deinit()
{
	PROFILE_FUNC();
	CLEM_LOG_INFO("core", "keyboard deinit");
}

#endif
} // namespace clem