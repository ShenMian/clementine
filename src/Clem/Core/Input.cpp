// Copyright 2021 SMS
// License(Apache-2.0)

#include "Input.h"
#include "Clem/Event/EventDispatcher.h"
#include "Clem/Event/KeyEvent.h"
#include "Clem/Event/MouseEvent.h"
#include "Clem/Platform.h"

#ifdef OS_UNIX

void Input::update()
{
}

#endif

#ifdef OS_WIN

void Input::update()
{
	static auto&        dispatcher = EventDispatcher::getInstance();
	static HANDLE       hOut       = GetStdHandle(STD_INPUT_HANDLE);
	static INPUT_RECORD rec;
	static DWORD        res;
	ReadConsoleInput(hOut, &rec, 1, &res); // 堵塞
	switch(rec.EventType)
	{
	case KEY_EVENT:
		dispatcher.dispatch(
				KeyEvent(rec.Event.KeyEvent.wVirtualKeyCode,
								 rec.Event.KeyEvent.bKeyDown,
								 rec.Event.KeyEvent.wRepeatCount));
		break;

	case MOUSE_EVENT:
		switch(rec.Event.MouseEvent.dwEventFlags)
		{
		case MOUSE_MOVED:
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
}

#endif