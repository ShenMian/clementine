// Copyright 2020 SMS
// License(Apache-2.0)
// 输入组件

#ifndef CLEM_INPUT_COMPONENT_H_
#define CLEM_INPUT_COMPONENT_H_

typedef unsigned short ushort;

#include <map>
#include <vector>

class Input
{
public:
	virtual void update() = 0;

	void bind(ushort code, ushort event);

	void   setInterval(ushort ms);
	ushort getInterval() const;

protected:
	std::map<ushort, ushort> index;
	std::vector<ushort>      events;
	ushort                   interval = 150; // 重复响应持续相同按键的时间
};

#endif // CLEM_INPUT_COMPONENT_H_
