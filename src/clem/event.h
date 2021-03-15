// Copyright 2021 SMS
// License(Apache-2.0)
// 事件

#ifndef CLEM_EVENT_H_
#define CLEM_EVENT_H_

/**
 * @brief 事件.
 */
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

