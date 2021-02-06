// Copyright 2020 SMS
// License(Apache-2.0)
// 输入

#ifndef CLEM_INPUT_COMPONENT_H_
#define CLEM_INPUT_COMPONENT_H_

#include <map>
#include <vector>
#include "observable.h"

typedef unsigned short ushort;
typedef ushort         InputEvent;

class Input : public Observable
{
public:
	void         update();
	virtual void scan() = 0;

	void notifyObserver() const override;

	const std::vector<InputEvent> getEvents() const;
	void                          bind(ushort code, const InputEvent& event);

	void   setInterval(ushort ms);
	ushort getInterval() const;

protected:
	std::map<ushort, InputEvent> index;
	std::vector<InputEvent>      events;
	ushort                       interval = 150; // 重复响应持续相同按键的时间
};

#endif // !CLEM_INPUT_COMPONENT_H_
