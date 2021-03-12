// Copyright 2020 SMS
// License(Apache-2.0)
// 组件

#ifndef CLEM_COMPONENT_H_
#define CLEM_COMPONENT_H_

#include "factor.h"

/// 组件
class Component
{
public:
	Component();

	virtual void update(float dt);

	virtual void onAdd();
	virtual void onRemove();

	void    setOwner(Factor* owner);
	Factor* getOwner() const;

protected:
	Factor* owner;
};

#endif // !CLEM_COMPONENT_H_

