// Copyright 2020 SMS
// License(Apache-2.0)
// ÊÂ¼þ

#ifndef CLEM_EVENT_H_
#define CLEM_EVENT_H_

class Event
{
public:
	enum class Type;
    
	Event(Type type);

	Type getType() const;

private:
	Type type;
};

enum class Event::Type
{
  keyboard,
  gamepad
};

#endif // !CLEM_EVENT_H_

