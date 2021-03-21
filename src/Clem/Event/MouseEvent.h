// Copyright 2021 SMS
// License(Apache-2.0)

#ifndef CLEM_EVENT_MOUSE_EVENT_H_
#define CLEM_EVENT_MOUSE_EVENT_H_

#include "Event.h"
#include "Clem/Math/Vec2.h"

class MouseEvent : public Event
{
public:
	EVENT_CLASS_TYPE(mouse);

	enum class Type
	{
		move,
		click,
		wheeled
	};

	enum class State
	{
		left_buttom,
		right_buttom,
		none
	};

	MouseEvent(Type type, const Point& pos, State state = State::none);

	const Point& getPosition() const;
	State        getState() const;
	Type         getType() const;

private:
	Type  type;
	Point position;
	State state;
};

#endif // !CLEM_EVENT_MOUSE_EVENT_H_
