// Copyright 2020 SMS
// License(Apache-2.0)
// ×é¼þ

#ifndef CLEM_COMPONENT_H_
#define CLEM_COMPONENT_H_

#include "factor.h"

class Component
{
public:
	Component();

	virtual void update() = 0;

	virtual void onEnter();
	virtual void onExit();
	virtual void onAdd();
	virtual void onRemove();

	void    setOwner(Factor* owner);
	Factor* getOwner() const;

protected:
	Factor* owner;
};

#endif // !CLEM_COMPONENT_H_

