// Copyright 2021 SMS
// License(Apache-2.0)

#include "Input.h"
#include "Clem/Event/EventDispatcher.h"
#include "Clem/Event/KeyEvent.h"
#include "Clem/Event/MouseEvent.h"
#include "Clem/Platform.h"
#include "Clem/Profiler.h"
#include "Keyboard.h"
#include "Mouse.h"

#ifdef OS_UNIX

void Input::update()
{
	PROFILE_FUNC();
}

#endif

#ifdef OS_WIN

void Input::update()
{
	PROFILE_FUNC();

	static auto&        dispatcher = EventDispatcher::getInstance();
	static HANDLE       hIn        = GetStdHandle(STD_INPUT_HANDLE);
	static INPUT_RECORD rec;
	static DWORD        res;

	DWORD numOfEvents;
	GetNumberOfConsoleInputEvents(hIn, &numOfEvents);
	if(numOfEvents < 1)
		return;

	ReadConsoleInput(hIn, &rec, 1, &res);
	// PeekConsoleInput(hIn, &rec, 1, &res);

	KEY_EVENT_RECORD keyEvent;

	switch(rec.EventType)
	{
	case KEY_EVENT:
		keyEvent = rec.Event.KeyEvent;
		Keyboard::setKeyState((Keyboard::Key)keyEvent.wVirtualKeyCode, keyEvent.bKeyDown);
		dispatcher.dispatch(
				KeyEvent(keyEvent.wVirtualKeyCode,
								 keyEvent.bKeyDown,
								 keyEvent.wRepeatCount));
		break;

	case MOUSE_EVENT:
		switch(rec.Event.MouseEvent.dwEventFlags)
		{
		case MOUSE_MOVED:
			Mouse::setPosition({rec.Event.MouseEvent.dwMousePosition.X,
													rec.Event.MouseEvent.dwMousePosition.Y});
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::move,
																		 {(float)rec.Event.MouseEvent.dwMousePosition.X,
																			(float)rec.Event.MouseEvent.dwMousePosition.Y}));
			break;

		case DOUBLE_CLICK:
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::double_click,
																		 {(float)rec.Event.MouseEvent.dwMousePosition.X,
																			(float)rec.Event.MouseEvent.dwMousePosition.Y}));
			break;

		case MOUSE_WHEELED:
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::wheeled,
																		 {(float)rec.Event.MouseEvent.dwMousePosition.X,
																			(float)rec.Event.MouseEvent.dwMousePosition.Y}));
			break;
		}
		if(rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																		 {(float)rec.Event.MouseEvent.dwMousePosition.X,
																			(float)rec.Event.MouseEvent.dwMousePosition.Y},
																		 MouseEvent::Key::left_buttom));
		if(rec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED)
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																		 {(float)rec.Event.MouseEvent.dwMousePosition.X,
																			(float)rec.Event.MouseEvent.dwMousePosition.Y},
																		 MouseEvent::Key::right_buttom));
		break;

	case WINDOW_BUFFER_SIZE_EVENT:
		break;
	}

	Mouse::setKeyState(Mouse::Key::left, rec.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
	Mouse::setKeyState(Mouse::Key::right, rec.Event.MouseEvent.dwButtonState & RIGHTMOST_BUTTON_PRESSED);
}

#endif