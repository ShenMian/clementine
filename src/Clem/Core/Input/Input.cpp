// Copyright 2021 SMS
// License(Apache-2.0)

#include "Input.h"
#include "Clem/Events/EventDispatcher.h"
#include "Clem/Events/KeyEvent.h"
#include "Clem/Events/MouseEvent.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Clem/Log.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace clem
{
#ifdef OS_UNIX

void Input::update()
{
	PROFILE_FUNC();

	char ch = -1;
	ch      = getchar();
	if(ch == -1)
		return;
	auto vk = ch;
	Keyboard::setKeyState((Keyboard::Key)vk, true);
}

#	include <termios.h>
#	include <unistd.h>

void Input::init()
{
	PROFILE_FUNC();
	CLEM_CORE_INFO("input init");

	termios opts;
	tcgetattr(0, &opts);          // grab old terminal i/o settings
	opts.c_lflag &= ~ICANON;      // disable buffered i/o
	opts.c_lflag &= ~ECHO;        // set echo mode
	tcsetattr(0, TCSANOW, &opts); // use these new terminal i/o settings now
}

void Input::deinit()
{
	PROFILE_FUNC();
	CLEM_CORE_INFO("input deinit");

	termios opts;
	tcgetattr(0, &opts);
	opts.c_lflag &= ICANON;
	opts.c_lflag &= ECHO;
	tcsetattr(0, TCSANOW, &opts);
}

#endif

#ifdef OS_WIN

void handleKeyEvent(KEY_EVENT_RECORD* e)
{
	Keyboard::setKeyState((Keyboard::Key)e->wVirtualKeyCode, e->bKeyDown);
	EventDispatcher::get().dispatch(
			KeyEvent(e->wVirtualKeyCode,
							 e->bKeyDown,
							 e->wRepeatCount));
}

void handleMouseEvent(MOUSE_EVENT_RECORD* e)
{
	auto& dispatcher = EventDispatcher::get();
	switch(e->dwEventFlags)
	{
	case MOUSE_MOVED:
		Mouse::setPosition({(float)e->dwMousePosition.X,
												(float)e->dwMousePosition.Y});
		dispatcher.dispatch(MouseEvent(MouseEvent::Type::move,
																	 {(float)e->dwMousePosition.X,
																		(float)e->dwMousePosition.Y}));
		break;

	case DOUBLE_CLICK:
		dispatcher.dispatch(MouseEvent(MouseEvent::Type::double_click,
																	 {(float)e->dwMousePosition.X,
																		(float)e->dwMousePosition.Y}));
		break;

	case MOUSE_WHEELED:
		dispatcher.dispatch(MouseEvent(MouseEvent::Type::wheeled,
																	 {(float)e->dwMousePosition.X,
																		(float)e->dwMousePosition.Y}));
		break;
	}
	if(e->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																	 {(float)e->dwMousePosition.X,
																		(float)e->dwMousePosition.Y},
																	 MouseEvent::Key::left_buttom));
	if(e->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
		dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																	 {(float)e->dwMousePosition.X,
																		(float)e->dwMousePosition.Y},
																	 MouseEvent::Key::right_buttom));
	Mouse::setKeyState(Mouse::Key::left, e->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
	Mouse::setKeyState(Mouse::Key::right, e->dwButtonState & RIGHTMOST_BUTTON_PRESSED);
}

void Input::update()
{
	PROFILE_FUNC();

	static auto&        dispatcher = EventDispatcher::get();
	static HANDLE       hIn        = GetStdHandle(STD_INPUT_HANDLE);
	static INPUT_RECORD rec;
	static DWORD        res;

	DWORD numOfEvents;
	GetNumberOfConsoleInputEvents(hIn, &numOfEvents);
	if(numOfEvents < 1)
		return;

	ReadConsoleInput(hIn, &rec, 1, &res);

	switch(rec.EventType)
	{
	case KEY_EVENT:
		handleKeyEvent(&rec.Event.KeyEvent);
		break;

	case MOUSE_EVENT:
		handleMouseEvent(&rec.Event.MouseEvent);
		break;

	case WINDOW_BUFFER_SIZE_EVENT:
		break;
	}
}

void Input::init()
{
	PROFILE_FUNC();
	CLEM_CORE_INFO("input init");
}

void Input::deinit()
{
	PROFILE_FUNC();
	CLEM_CORE_INFO("input deinit");
}

#endif
} // namespace clem