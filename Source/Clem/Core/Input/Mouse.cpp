// Copyright 2021 SMS
// License(Apache-2.0)

#include "Mouse.h"
#include "Events/EventDispatcher.h"
#include "Events/MouseEvent.h"
#include "Platform.h"
#include "Profiler.h"
#include "Input.h"
#include <cassert>

namespace clem
{

std::unordered_map<Mouse::Key, bool> Mouse::states;
Point2                               Mouse::position;

bool Mouse::getKeyState(Key k)
{
	if(states.find(k) != states.end())
		return states[k];
	else
		return false;
}

void Mouse::setKeyState(Key k, bool s)
{
	states[k] = s;
}

Point2 Mouse::getPosition()
{
	return position;
}

void Mouse::setPosition(Point2 p)
{
	position = p;
}

#ifdef OS_UNIX

void Mouse::update()
{
}

#endif

#ifdef OS_WIN

void Mouse::update()
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
		if(record.EventType != MOUSE_EVENT)
			continue;

		const MOUSE_EVENT_RECORD* mouseRecord = &record.Event.MouseEvent;
		auto&                     dispatcher  = EventDispatcher::get();
        /*
		switch(mouseRecord->dwEventFlags)
		{
		case MOUSE_MOVED:
			Mouse::setPosition({(float)mouseRecord->dwMousePosition.X,
													(float)mouseRecord->dwMousePosition.Y});
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::move,
																		 {(float)mouseRecord->dwMousePosition.X,
																			(float)mouseRecord->dwMousePosition.Y}));
			break;

		case DOUBLE_CLICK:
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::double_click,
																		 {(float)mouseRecord->dwMousePosition.X,
																			(float)mouseRecord->dwMousePosition.Y}));
			break;

		case MOUSE_WHEELED:
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::wheeled,
																		 {(float)mouseRecord->dwMousePosition.X,
																			(float)mouseRecord->dwMousePosition.Y}));
			break;
		}
		if(mouseRecord->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																		 {(float)mouseRecord->dwMousePosition.X,
																			(float)mouseRecord->dwMousePosition.Y},
																		 MouseEvent::Key::left_buttom));
		if(mouseRecord->dwButtonState & RIGHTMOST_BUTTON_PRESSED)
			dispatcher.dispatch(MouseEvent(MouseEvent::Type::click,
																		 {(float)mouseRecord->dwMousePosition.X,
																			(float)mouseRecord->dwMousePosition.Y},
																		 MouseEvent::Key::right_buttom));
		Mouse::setKeyState(Mouse::Key::left, mouseRecord->dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED);
		Mouse::setKeyState(Mouse::Key::right, mouseRecord->dwButtonState & RIGHTMOST_BUTTON_PRESSED);
		*/
	}

	for(size_t i = 0; i < inputRecords.size(); i++)
		if(inputRecords[i].EventType == MOUSE_EVENT)
			inputRecords.erase(inputRecords.begin() + i);
}

#endif
} // namespace clem