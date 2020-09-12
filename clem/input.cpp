// Copyright 2020 SMS
// License(Apache-2.0)
// 输入

#include "input.h"

void Input::bind(ushort code, ushort event)
{
	auto ret = index.find(code);
	if(ret == index.end())
		index.insert({code, event});
	else
		ret->second = event;
}

void Input::setInterval(ushort ms)
{
	interval = ms;
}

ushort Input::getInterval() const
{
	return interval;
}
