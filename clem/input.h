// Copyright 2020 SMS
// License(Apache-2.0)
// ����

#ifndef CLEM_INPUT_COMPONENT_H_
#define CLEM_INPUT_COMPONENT_H_

typedef unsigned short ushort;

#include <map>
#include <vector>
#include "observable.h"

class Input : public Observable
{
public:
	virtual void update() = 0;

	void bind(ushort code, ushort event);

	void   setInterval(ushort ms);
	ushort getInterval() const;

protected:
	std::map<ushort, ushort> index;
	std::vector<ushort>      events;
	ushort                   interval = 150; // 重复响应持续相同按键的时�?
};

#endif // CLEM_INPUT_COMPONENT_H_
